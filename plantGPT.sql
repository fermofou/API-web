CREATE DATABASE PlantGPT;
use PlantGPT;

CREATE TABLE sensores(
    `sensor_id` int  auto_increment primary KEY,
    `device_name` varchar(20)
);

CREATE table log_humedad (
	log_id int primary key auto_increment,
    log_time timestamp,
    humedad float,
    `id_sensor` INT null,
    FOREIGN KEY (`id_sensor`) REFERENCES `sensores`(`sensor_id`)
);

CREATE TABLE log_luz (
	log_id int primary key auto_increment,
    log_time timestamp,
    luz_solar float,
    `id_sensor` INT null,
    FOREIGN KEY (`id_sensor`) REFERENCES `sensores`(`sensor_id`)
);

CREATE TABLE log_temp (
	log_id int primary key auto_increment,
    log_time timestamp ,
    temperatura float,
    `id_sensor` INT null,
    FOREIGN KEY (`id_sensor`) REFERENCES `sensores`(`sensor_id`)
);

CREATE TABLE log_movimiento (
	log_id int primary key auto_increment,
    log_time timestamp ,
    movimiento BOOLEAN,
    `id_sensor` INT null,
    FOREIGN KEY (`id_sensor`) REFERENCES `sensores`(`sensor_id`)
);

CREATE TABLE log_distancia (
	log_id int primary key auto_increment,
    log_time timestamp,
    distancia float,
    `id_sensor` INT null,
    FOREIGN KEY (`id_sensor`) REFERENCES `sensores`(`sensor_id`)
);
INSERT INTO sensores (device_name) VALUES
    ('Sensor_Movimiento'),
    ('Sensor_Distancia'),
    ('Sensor_Luz'),
    ('Sensor_Temperatura'),
    ('Sensor_Humedad');

