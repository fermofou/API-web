const express =require('express');
const bodyParser =require('body-parser');
const cors =require('cors');
const fs=require('fs');
const morgan =require('morgan');
const path =require('path')
const router=require('./routes/route');
//  Paso 1. Crear el servidor con express
const app= express();

app.use(cors())

app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());
app.use(morgan('dev'))

var accessLogStream = fs.createWriteStream(path.join(__dirname,'/logs/access.log'),{flags: 'a'})
//setup logger
app.use(morgan('combined',{ stream: accessLogStream}))
app.use(router);

app.get('/',(req,res)=>{
    res.send('Hello world!')
})
const port=3000

app.listen(port,()=>{
    console.log('Server started running on : '+ port);
})