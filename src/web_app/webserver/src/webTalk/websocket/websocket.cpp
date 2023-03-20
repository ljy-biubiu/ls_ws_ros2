// Copyright (c) 2022，Horizon Robotics.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "websocket/websocket.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

namespace websocket
{

  Websocket::Websocket()
  {
    uws_server_ = std::make_shared<UwsServer>();
    if (uws_server_->Init())
    {
      throw std::runtime_error("Websocket Init uWS server failed");
    }

    if (!worker_)
    {
      worker_ = std::make_shared<std::thread>(
          std::bind(&Websocket::MessageProcess, this));
    }

    data_send_thread_.CreatThread(1);

    // sendMsg = new std::thread([=]()
    //                           {
    //   while(1)
    //   {
    //       char res[512] = {0};
    //       fgets(res,sizeof(res)-1,stdin);
    //       printf("send to client:%s",res);
    //       std::string msg(res,strlen(res));
    //       my_queue.push(msg);
    //   } });
  }

  std::string Websocket::packageJson(const std::string &name, const std::string &data)
  {
    rapidjson::StringBuffer buf;
    // rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);

    writer.StartObject();

    writer.Key(name.c_str());
    writer.String(data.c_str());
    writer.EndObject();

    return buf.GetString();


    // Json::Value root;
    // Json::FastWriter writer;
    // root[name] = Json::Value(data);
    // return writer.write(root);
  }

  void Websocket::pushData(const std::vector<std::string> &msg)
  {
    my_mutex.lock();
    my_queue.push(msg);
    my_mutex.unlock();
  }

  Websocket::~Websocket()
  {
    {
      if (worker_ && worker_->joinable())
      {
        map_stop_ = true;
        // map_smart_condition_.notify_one();
        worker_->join();
        worker_ = nullptr;
      }
    }
    uws_server_->DeInit();
  }

  int Websocket::SendMessage(const std::vector<std::string> &msg)
  {
    // // fps control
    // if (output_fps_ > 0 && output_fps_ <= 30)
    // {
    //   send_frame_count_++;
    //   if (send_frame_count_ % (30 / output_fps_) != 0)
    //   {
    //     return 0;
    //   }
    //   if (send_frame_count_ >= 1000)
    //     send_frame_count_ = 0;
    // }

    std::string final_data = packageJson(msg.at(CONTENT_NAME), msg.at(CONTENT_DATA));

    uws_server_->Send(final_data);
    return 0;
  }

  void Websocket::MessageProcess()
  {
    while (!map_stop_)
    {
      while (!my_queue.empty())
      {
        auto frame = my_queue.front();
        int task_num = data_send_thread_.GetTaskNum();
        if (task_num < 3)
        {
          data_send_thread_.PostTask(
              std::bind(&Websocket::SendMessage, this, frame));
        }
        my_queue.pop();
      }

      if (my_queue.size() > 2)
      {
        my_queue.pop();
        std::cout << "web socket has cache image num > 20, size " << my_queue.size() << std::endl;
      }

      if (uws_server_->get_rec_queue().size() != 0)
      {
        // std::cout << uws_server_->get_rec_queue().front() << std::endl;
        if (parse_json_data(uws_server_->get_rec_queue().front()))
          ;
        uws_server_->get_rec_queue().pop();
      }

      usleep(1 * 1000);
    }
  }

  int Websocket::parse_json_data(const std::string &json_data)
  {
    rapidjson::Document dom;
    if (!dom.Parse(json_data.c_str()).HasParseError())
    {
      if (dom.HasMember("lidar_ip") && dom["lidar_ip"].IsString())
      {
        std::cout << "lidar_ip : " << dom["lidar_ip"].GetString() << std::endl;
        return 1;
      }
    }
    return 0;
  }

} // namespace websocket

// rapidjson::Document dom;
// 	if (!dom.Parse(json_content.c_str()).HasParseError()) {
// 		if (dom.HasMember("name") && dom["name"].IsString()) {
// 			fprintf(stdout, "name: %s\n", dom["name"].GetString());
// 		}