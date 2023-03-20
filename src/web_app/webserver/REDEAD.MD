## 启动
1.启动nginx代理
   - cd "nginx_space" && sudo sbin/nginx
   - 浏览器打开 http://127.0.0.1:3000/ws_test_web/web_talk/html/monitor.html
   - 能显示网页则代表nginx顺利启动

2.启动websokcet服务器
   - cd "ros2_ws" && source install/setup.bash
   - ros2 run mywebsocket mywebsocket

