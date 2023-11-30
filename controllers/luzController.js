const mysql = require('../database/db')

class MainController {

    async logLuz(req , res){
        console.log(req.params.luz_solar)
        console.log(req.params.id_sensor)
        if(req.params.id_sensor != null && req.params.luz_solar != null) {
            let id_sensor = req.params.id_sensor
            let luz_solar = req.params.luz_solar;
            var sql = `insert into log_luz (log_time, id_sensor, luz_solar) values (now(), ${id_sensor}, ${luz_solar});`
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
    
    async getLuzLogs(req,res){
        console.log("Get Logs")
        console.log(req.params.log_id)
        if(req.params.log_id!=null){
            let log_id = req.params.log_id;
            var sql = `SELECT * FROM log_luz where log_id='${log_id}'`
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

const luzController = new MainController()
module.exports = luzController;