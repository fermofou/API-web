const mysql =require('../database/db')

class MainController{
    async logDistancia(req,res){
        console.log(req.params.distancia)
        console.log(req.params.id_sensor)
        if(req.params.id_sensor!=null && req.params.distancia!= null){
            let id_sensor = req.params.id_sensor
            let distancia= req.params.distancia;
            var sql =`insert into log_distancia (log_time,id_sensor, distancia) values (now(),${id_sensor},${distancia});`
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
    async getDistanceLogs(req,res){
        console.log("Get logs")
        console.log(req.params.log_id)
        if(req.params.log_id!=null){
            let log_id = req.params.log_id;
            var sql = `SELECT * FROM log_distancia where log_id='${log_id}'`
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

const distanceController = new MainController()
module.exports = distanceController;