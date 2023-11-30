const mysql =require('../database/db')

class MainController{
    async logMov(req,res){
        console.log(req.params.movimiento)
        console.log(req.params.id_sensor)
        if(req.params.id_sensor!=null && req.params.movimiento!= null){
            let id_sensor = req.params.id_sensor
            let movimiento= req.params.movimiento;
            var sql =`insert into log_movimiento (log_time,id_sensor, movimiento) values (now(),${id_sensor},${movimiento});`
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
    async getMovimientoLogs(req,res){
        console.log("Get logs")
        console.log(req.params.log_id)
        if(req.params.log_id!=null){
            let log_id = req.params.log_id;
            var sql = `SELECT * FROM log_movimiento where log_id='${log_id}'`
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

const movController = new MainController()
module.exports = movController;