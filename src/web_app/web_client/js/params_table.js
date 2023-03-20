// //将表单转化为JSON对象
// function fromToJson(form) {
// 	var result = {};
// 	//获取表单的数组对象
// 	var fieldArray = $('#' + form).serializeArray();
// 	//将表单转化为JSON对象
// 	for (var i = 0; i < fieldArray.length; i++) {
// 		var field = fieldArray[i];
// 		if (field.name in result) {
// 			result[field.name] += ',' + field.value;
// 		} else {
// 			result[field.name] = field.value;
// 		}
// 	}
// 	return result;
// }

var table_send_flag = false;
var jsonText_final;


function serializeForm(form) {
	var obj = {};
	$.each(form.serializeArray(), function (index) {
		if (obj[this['name']]) {
			obj[this['name']] = obj[this['name']] + ',' + this['value'];
		} else {
			obj[this['name']] = this['value'];
		}
	});
	return obj;
}



window.onload = function () {


	var btn_1 = document.getElementById("btn_1");
	var close = document.getElementsByClassName("close");
	var form_1 = document.getElementsByClassName("form_1");
	var comfirm_save_params = document.getElementById("comfirm_save_params");

	var params_obj = {
		"lidar_ip": "null",
		"lidar_data_port": "null ",
		"lidar_device_port": "null",
		"result_ip": "null ",
		"result_port": "null",
		"video_url": "null ",
		"debug": "null",

		"log_flag": "null ",
		"filter_flag": "null",
		"filter_x_min": "null ",
		"filter_x_max": "null",
		"filter_y_min": "null ",
		"filter_y_max": "null",
		"filter_z_min": "null ",
		"filter_z_max": "null",

		"transform_flag": "null ",
		"pitch": "null",
		"roll": "null ",
		"yaw": "null",
		"x_offset": "null ",
		"y_offset": "null",
		"z_offset": "null ",
		"calculate_calibration_param": "null",
		"save_pcd": "null ",

		"pcd_path": "null",
		"points_txt_path": "null ",
		"mosaic_image_height": "null",
		"mosaic_image_width": "null ",
		"pixel_grid_size": "null",
		"pixel_x_min": "null ",
		"pixel_x_max": "null",
		"pixel_y_min": "null ",
		"pixel_y_max": "null",
		"move_origin": "null ",
	};



	comfirm_save_params.addEventListener('click', function () {

		let jsonText_first = JSON.stringify(params_obj);

		let json_obj = JSON.parse(jsonText_first);

		// json_obj.lidar_ip

		json_obj.lidar_ip = document.getElementById("lidar_ip").value;
		json_obj.lidar_data_port = document.getElementById("lidar_data_port").value;
		json_obj.lidar_device_port = document.getElementById("lidar_device_port").value;
		json_obj.result_ip = document.getElementById("result_ip").value;
		json_obj.result_port = document.getElementById("result_port").value;
		json_obj.video_url = document.getElementById("video_url").value;
		json_obj.debug = document.getElementById("debug").value;
		json_obj.log_flag = document.getElementById("log_flag").value;
		json_obj.filter_flag = document.getElementById("filter_flag").value;
		json_obj.filter_x_min = document.getElementById("filter_x_min").value;
		json_obj.filter_x_max = document.getElementById("filter_x_max").value;
		json_obj.filter_y_min = document.getElementById("filter_y_min").value;
		json_obj.filter_y_max = document.getElementById("filter_y_max").value;
		json_obj.filter_z_min = document.getElementById("filter_z_min").value;
		json_obj.filter_z_max = document.getElementById("filter_z_max").value;
		json_obj.transform_flag = document.getElementById("transform_flag").value;
		json_obj.pitch = document.getElementById("pitch").value;
		json_obj.roll = document.getElementById("roll").value;
		json_obj.yaw = document.getElementById("yaw").value;
		json_obj.x_offset = document.getElementById("x_offset").value;
		json_obj.y_offset = document.getElementById("y_offset").value;
		json_obj.z_offset = document.getElementById("z_offset").value;
		json_obj.calculate_calibration_param = document.getElementById("calculate_calibration_param").value;
		json_obj.save_pcd = document.getElementById("save_pcd").value;

		json_obj.pcd_path = document.getElementById("pcd_path").value;
		json_obj.points_txt_path = document.getElementById("points_txt_path").value;
		json_obj.mosaic_image_height = document.getElementById("mosaic_image_height").value;
		json_obj.mosaic_image_width = document.getElementById("mosaic_image_width").value;
		json_obj.pixel_grid_size = document.getElementById("pixel_grid_size").value;
		json_obj.pixel_x_min = document.getElementById("pixel_x_min").value;
		json_obj.pixel_x_max = document.getElementById("pixel_x_max").value;
		json_obj.pixel_y_min = document.getElementById("pixel_y_min").value;
		json_obj.pixel_y_max = document.getElementById("pixel_y_max").value;
		json_obj.move_origin = document.getElementById("move_origin").value;

		jsonText_final = JSON.stringify(json_obj);
		//console.log(lidar_ip);
		//console.log(lidar_ip.value);
		//console.log("qweqwewqdqw");
		console.log(jsonText_final);
		table_send_flag = true;
	})

	//var comfirm_save = document.getElementById("comfirm_save");

	btn_1.addEventListener('click', function () {
		form_1[0].className = "form_1 open";
		console.log(form_1);
	})
	close[0].addEventListener('click', function () {
		form_1[0].className = "form_1";
		console.log(form_1);
	})
	// comfirm_save.addEventListener('click', function () {
	// 	// // console.log(fromToJson("form_1"));
	// 	// // console.log("=============222==============");
	// 	// var jsonObj = serializeForm($("form_1"));

	// 	// var jsonStr = JSON.stringify(jsonObj);
	// 	// console.log(form_1);
	// 	var formData = new FormData(form_1); 
	// 	console.log(formData);

	// })


	// console.log("===========================");
	// form_1.addEventListener('click', function () {
	// 	// console.log(fromToJson("form_1"));
	// 	console.log("==========================2=");
	// })

	// while(1)
	// {
	// 	var a=1000;
	// 	a--;
	// 	if(a==0)
	// 	{
	// 		break;
	// 	}
	// }
	// console.log("111111111111111111111111111111111111");

}
