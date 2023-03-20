var ws;
var jsonObj;
var flag_test = 0;
var receive_image_data;
var receive_lidar_data;
var receive_params_data;

$(function () {
    ws = new WebSocket("ws://127.0.0.1:3001");

    ws.onopen = function () {
        console.log('onopen');
    };
    ws.onclose = function () {
        $('#message').text('Lost connection.');
        console.log('onclose');
    };
    ws.onmessage = function (message) {
        //console.log("got '" + message.data + "'");
        //eval(message.data);
	//console.log("data:"+message.data)
	//image_data = message.data;
	console.log(message.data)
	jsonObj = window.JSON.parse(message.data);

       if(jsonObj.lidar)
       {
	  flag_test = 1;
          receive_lidar_data = window.JSON.parse(jsonObj.lidar);
       }
       else if(jsonObj.image)
       {
         console.log("image")
         receive_image_data = jsonObj.image;
       }
       else if(jsonObj.params)
       {
         console.log("params")
         receive_params_data = jsonObj.params;
       }
       else
       {
         console.log("error message type")
       }
    };
    ws.onerror = function (error) {
        console.log('onerror ' + error);
        console.log(error);
    };
});


