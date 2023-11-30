const mysql =require('../database/db')

class MainController{
    async logTemp(req,res){
        console.log(req.params.temperatura)
        console.log(req.params.id_sensor)
        if(req.params.id_sensor!=null && req.params.temperatura!= null){
            let id_sensor = req.params.id_sensor
            let temperatura= req.params.temperatura;
            var sql =`insert into log_temp (log_time,id_sensor, temperatura) values (now(),${id_sensor},${temperatura});`
            mysql.query(sql, (error, data, fields)=>{
                if(error){
                    res.status(500)
                    res.send(error.message)
                }else{
                    console.log(data)
                    res.json({
                        status: 200,
                        message: "Log uploaded successfully",
                        affectedRows:data.affectedRows
                    })
                }
            })
        } else{
            res.send('Por favor llena todos los datos!')
        }

    }
    async getTempLogs(req,res){
        console.log("Get logs")
        console.log(req.params.log_id)
        if(req.params.log_id!=null){
            let log_id = req.params.log_id;
            var sql = `SELECT * FROM log_temp where log_id='${log_id}'`
            mysql.query(sql, (error, data, fields)=>{
                if(error){
                    res.status(500)
                    res.send(error.message)
                }else{
                    console.log(data)
                    res.json({data
                    })
                }
            })
        }
    }
}

const tempController = new MainController()
module.exports = tempController;