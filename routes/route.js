const express =require('express')
const tempController = require('../controllers/tempController')
const distanceController = require('../controllers/distanceController')
const humidController = require('../controllers/humidController')
const sensorMovimiento = require('../controllers/sensorMovimiento')
const luzController = require('../controllers/luzController')




const router = express.Router()

router.get('/api/getTempLogs/:log_id',tempController.getTempLogs);
router.post('/api/logTemp/:id_sensor/:temperatura',tempController.logTemp);
router.get('/api/getDistanceLogs/:log_id',distanceController.getDistanceLogs);
router.post('/api/logDistancia/:id_sensor/:distancia',distanceController.logDistancia);
router.get('/api/getHumidLogs/:log_id',humidController.getHumidLogs);
router.post('/api/logHumid/:id_sensor/:humedad',humidController.logHumid);
router.get('/api/getMovimientoLogs/:log_id',sensorMovimiento.getMovimientoLogs);
router.post('/api/logMov/:id_sensor/:movimiento',sensorMovimiento.logMov);
router.get('/api/getLuzLogs/:log_id',luzController.getLuzLogs);
router.post('/api/logLuz/:id_sensor/:luz_solar',luzController.logLuz);

module.exports = router;