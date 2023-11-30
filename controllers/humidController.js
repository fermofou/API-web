const mysql = require('../database/db')

class MainController {

    async logHumid(req , res){
        console.log(req.params.humedad)
        console.log(req.params.id_sensor)
        if(req.params.id_sensor != null && req.params.humedad != null) {
            let id_sensor = req.params.id_sensor
            let humedad = req.params.humedad;
            var sql = `insert into log_humedad (log_time, id_sensor, humedad) values (now(), ${id_sensor}, ${humedad});`
            mysql.query(sql, (error,data,fields) => {
                if(error) {
                    res.status(500)
                    res.send(error.message)
                } else {
                    console.log(data)
                    res.json({
                        status: 200,
                        message: "Log uploaded successfully",
                        affectedRows: data.affectedRows
                    })
                }
            })
        } else {
          res.send('Por favor llena todos los datos!')
        }
    }
    
    async getHumidLogs(req,res){
        console.log("Get Logs")
        console.log(req.params.log_id)
        if(req.params.log_id!=null){
            let log_id = req.params.log_id;
            var sql = `SELECT * FROM log_humedad where log_id='${log_id}'`
            mysql.query(sql, (error, data, fields) => {//Vi que esta parte la cambiaste a execute, no se porque. query esta como execute en el que mandaste
                if(error) {                             //mysql.execute(sql,[id_sensor], (error, data, fields)=>{
                    res.status(500)                     //Asi es como lo tienes 
                    res.send(error.message)
                } else {
                    console.log(data)
                    res.json({
                        data
                    })
                }
            })
        }
    }
}

const humidController = new MainController()
module.exports = humidController;