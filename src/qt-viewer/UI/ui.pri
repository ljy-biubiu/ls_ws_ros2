SOURCES += \
    $$PWD/src/cameraviewer.cpp \
    $$PWD/src/alarm.cpp \
    $$PWD/src/diary.cpp \
    $$PWD/src/aboutdialog.cpp \
    $$PWD/src/imageWidget.cpp \
    $$PWD/src/paintarea.cpp \
    $$PWD/src/setroi.cpp \
    $$PWD/src/smsdialog.cpp \
    $$PWD/src/addlidar.cpp \
    $$PWD/src/titlebar.cpp \
    $$PWD/src/maintitlebar.cpp \
    $$PWD/src/childtitlebar.cpp \
    $$PWD/src/mainwindow.cpp \
    $$PWD/src/jsQt_chat.cpp \
    $$PWD/src/webui.cpp

HEADERS += \
    $$PWD/include/cameraviewer.h \
    $$PWD/include/alarm.h \
    $$PWD/include/diary.h \
    $$PWD/include/childtitlebar.h \
    $$PWD/include/maintitlebar.h \
    $$PWD/include/aboutdialog.h \
    $$PWD/include/imageWidget.h \
    $$PWD/include/paintarea.h \
    $$PWD/include/setroi.h \
    $$PWD/include/smsdialog.h \
    $$PWD/include/addlidar.h \
    $$PWD/include/titlebar.h \
    $$PWD/include/mainwindow.h \
    $$PWD/include/jsQt_chat.h \
    $$PWD/include/webui.h

FORMS += \
     $$PWD/src/cameraviewer.ui \
     $$PWD/src/alarm.ui \
     $$PWD/src/diary.ui \
     $$PWD/src/aboutdialog.ui \
     $$PWD/src/setroi.ui \
     $$PWD/src/smsdialog.ui \
     $$PWD/src/addpolygon.ui \
     $$PWD/src/maintitlebar.ui \
     $$PWD/src/childtitlebar.ui \
     $$PWD/src/addlidar.ui \
     $$PWD/src/webui.ui

INCLUDEPATH += $$PWD/include/.
INCLUDEPATH += $$PWD/src/.
INCLUDEPATH += $$PWD/forms/.

RESOURCES += \
    $$PWD/resource/images.qrc \
    $$PWD/resource/qss.qrc \
    $$PWD/resource/webSource.qrc \


#DISTFILES += \
#    $$PWD/resource/images/Button Refresh.png \
#    $$PWD/resource/images/Coordinate.png \
#    $$PWD/resource/images/Font \
#    $$PWD/resource/images/Font Awesome Cheatsheet.png \
#    $$PWD/resource/images/Grid.png \
#    $$PWD/resource/images/LSlogo1.png \
#    $$PWD/resource/images/Logo.png \
#    $$PWD/resource/images/OFF.png \
#    $$PWD/resource/images/ON.png \
#    $$PWD/resource/images/about_hover.png \
#    $$PWD/resource/images/about_normal.png \
#    $$PWD/resource/images/add.png \
#    $$PWD/resource/images/add_bottom.png \
#    $$PWD/resource/images/add_left.png \
#    $$PWD/resource/images/add_press.png \
#    $$PWD/resource/images/add_right.png \
#    $$PWD/resource/images/add_top.png \
#    $$PWD/resource/images/angle.png \
#    $$PWD/resource/images/background.png \
#    $$PWD/resource/images/bcjd.png \
#    $$PWD/resource/images/btn_close.png \
#    $$PWD/resource/images/btn_ok.png \
#    $$PWD/resource/images/clear.png \
#    $$PWD/resource/images/close.ico \
#    $$PWD/resource/images/close_hover.png \
#    $$PWD/resource/images/close_normal.png \
#    $$PWD/resource/images/closedata.png \
#    $$PWD/resource/images/cloud.png \
#    $$PWD/resource/images/down.png \
#    $$PWD/resource/images/dy.png \
#    $$PWD/resource/images/fushi.png \
#    $$PWD/resource/images/help.png \
#    $$PWD/resource/images/led_off.png \
#    $$PWD/resource/images/led_on.png \
#    $$PWD/resource/images/leishen.ico \
#    $$PWD/resource/images/logo (2).png \
#    $$PWD/resource/images/main.ico \
#    $$PWD/resource/images/max_hover.png \
#    $$PWD/resource/images/max_normal.png \
#    $$PWD/resource/images/min_hover.png \
#    $$PWD/resource/images/min_normal.png \
#    $$PWD/resource/images/msg_error.png \
#    $$PWD/resource/images/msg_info.png \
#    $$PWD/resource/images/msg_question.png \
#    $$PWD/resource/images/new.ico \
#    $$PWD/resource/images/normal_hover.png \
#    $$PWD/resource/images/normal_normal.png \
#    $$PWD/resource/images/open.png \
#    $$PWD/resource/images/pointcolor.png \
#    $$PWD/resource/images/qt_zh_CN.qm \
#    $$PWD/resource/images/reduce.png \
#    $$PWD/resource/images/reduce_press.png \
#    $$PWD/resource/images/save.ico \
#    $$PWD/resource/images/save.png \
#    $$PWD/resource/images/saveas.ico \
#    $$PWD/resource/images/select.png \
#    $$PWD/resource/images/setInitcoor.png \
#    $$PWD/resource/images/setting_normal.png \
#    $$PWD/resource/images/setting_pressed.png \
#    $$PWD/resource/images/sjqyxd.png \
#    $$PWD/resource/images/sms.png \
#    $$PWD/resource/images/title.png \
#    $$PWD/resource/images/trick.png \
#    $$PWD/resource/images/up.png \
#    $$PWD/resource/images/video.png \
#    $$PWD/resource/images/widgets.qm \
#    $$PWD/resource/images/writing_normal.png \
#    $$PWD/resource/images/writing_pressed.png \
#    $$PWD/resource/images/zhengshi.png \
#    $$PWD/resource/images/zuoshi.png \
#    $$PWD/resource/images/计算器_calculator-one (1).png \
#    $$PWD/resource/images/计算器_calculator-one.png \
#    $$PWD/resource/main.aps \
#    $$PWD/resource/main.ico \
#    $$PWD/resource/main.rc \
#    $$PWD/resource/qss/black.css \
#    $$PWD/resource/qss/black/add_bottom.png \
#    $$PWD/resource/qss/black/add_left.png \
#    $$PWD/resource/qss/black/add_right.png \
#    $$PWD/resource/qss/black/add_top.png \
#    $$PWD/resource/qss/black/branch_close.png \
#    $$PWD/resource/qss/black/branch_open.png \
#    $$PWD/resource/qss/black/calendar_nextmonth.png \
#    $$PWD/resource/qss/black/calendar_prevmonth.png \
#    $$PWD/resource/qss/black/checkbox_checked.png \
#    $$PWD/resource/qss/black/checkbox_checked_disable.png \
#    $$PWD/resource/qss/black/checkbox_parcial.png \
#    $$PWD/resource/qss/black/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/black/checkbox_unchecked.png \
#    $$PWD/resource/qss/black/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/black/radiobutton_checked.png \
#    $$PWD/resource/qss/black/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/black/radiobutton_unchecked.png \
#    $$PWD/resource/qss/black/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/blue.css \
#    $$PWD/resource/qss/blue/add_bottom.png \
#    $$PWD/resource/qss/blue/add_left.png \
#    $$PWD/resource/qss/blue/add_right.png \
#    $$PWD/resource/qss/blue/add_top.png \
#    $$PWD/resource/qss/blue/branch_close.png \
#    $$PWD/resource/qss/blue/branch_open.png \
#    $$PWD/resource/qss/blue/calendar_nextmonth.png \
#    $$PWD/resource/qss/blue/calendar_prevmonth.png \
#    $$PWD/resource/qss/blue/checkbox_checked.png \
#    $$PWD/resource/qss/blue/checkbox_checked_disable.png \
#    $$PWD/resource/qss/blue/checkbox_parcial.png \
#    $$PWD/resource/qss/blue/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/blue/checkbox_unchecked.png \
#    $$PWD/resource/qss/blue/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/blue/radiobutton_checked.png \
#    $$PWD/resource/qss/blue/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/blue/radiobutton_unchecked.png \
#    $$PWD/resource/qss/blue/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/darkblack.css \
#    $$PWD/resource/qss/darkblack/add_bottom.png \
#    $$PWD/resource/qss/darkblack/add_left.png \
#    $$PWD/resource/qss/darkblack/add_right.png \
#    $$PWD/resource/qss/darkblack/add_top.png \
#    $$PWD/resource/qss/darkblack/branch_close.png \
#    $$PWD/resource/qss/darkblack/branch_open.png \
#    $$PWD/resource/qss/darkblack/calendar_nextmonth.png \
#    $$PWD/resource/qss/darkblack/calendar_prevmonth.png \
#    $$PWD/resource/qss/darkblack/checkbox_checked.png \
#    $$PWD/resource/qss/darkblack/checkbox_checked_disable.png \
#    $$PWD/resource/qss/darkblack/checkbox_parcial.png \
#    $$PWD/resource/qss/darkblack/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/darkblack/checkbox_unchecked.png \
#    $$PWD/resource/qss/darkblack/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/darkblack/radiobutton_checked.png \
#    $$PWD/resource/qss/darkblack/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/darkblack/radiobutton_unchecked.png \
#    $$PWD/resource/qss/darkblack/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/darkblue.css \
#    $$PWD/resource/qss/darkblue/add_bottom.png \
#    $$PWD/resource/qss/darkblue/add_left.png \
#    $$PWD/resource/qss/darkblue/add_right.png \
#    $$PWD/resource/qss/darkblue/add_top.png \
#    $$PWD/resource/qss/darkblue/branch_close.png \
#    $$PWD/resource/qss/darkblue/branch_open.png \
#    $$PWD/resource/qss/darkblue/calendar_nextmonth.png \
#    $$PWD/resource/qss/darkblue/calendar_prevmonth.png \
#    $$PWD/resource/qss/darkblue/checkbox_checked.png \
#    $$PWD/resource/qss/darkblue/checkbox_checked_disable.png \
#    $$PWD/resource/qss/darkblue/checkbox_parcial.png \
#    $$PWD/resource/qss/darkblue/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/darkblue/checkbox_unchecked.png \
#    $$PWD/resource/qss/darkblue/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/darkblue/radiobutton_checked.png \
#    $$PWD/resource/qss/darkblue/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/darkblue/radiobutton_unchecked.png \
#    $$PWD/resource/qss/darkblue/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/darkgray.css \
#    $$PWD/resource/qss/darkgray/add_bottom.png \
#    $$PWD/resource/qss/darkgray/add_left.png \
#    $$PWD/resource/qss/darkgray/add_right.png \
#    $$PWD/resource/qss/darkgray/add_top.png \
#    $$PWD/resource/qss/darkgray/branch_close.png \
#    $$PWD/resource/qss/darkgray/branch_open.png \
#    $$PWD/resource/qss/darkgray/calendar_nextmonth.png \
#    $$PWD/resource/qss/darkgray/calendar_prevmonth.png \
#    $$PWD/resource/qss/darkgray/checkbox_checked.png \
#    $$PWD/resource/qss/darkgray/checkbox_checked_disable.png \
#    $$PWD/resource/qss/darkgray/checkbox_parcial.png \
#    $$PWD/resource/qss/darkgray/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/darkgray/checkbox_unchecked.png \
#    $$PWD/resource/qss/darkgray/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/darkgray/radiobutton_checked.png \
#    $$PWD/resource/qss/darkgray/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/darkgray/radiobutton_unchecked.png \
#    $$PWD/resource/qss/darkgray/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/flatwhite.css \
#    $$PWD/resource/qss/flatwhite/add_bottom.png \
#    $$PWD/resource/qss/flatwhite/add_left.png \
#    $$PWD/resource/qss/flatwhite/add_right.png \
#    $$PWD/resource/qss/flatwhite/add_top.png \
#    $$PWD/resource/qss/flatwhite/branch_close.png \
#    $$PWD/resource/qss/flatwhite/branch_open.png \
#    $$PWD/resource/qss/flatwhite/calendar_nextmonth.png \
#    $$PWD/resource/qss/flatwhite/calendar_prevmonth.png \
#    $$PWD/resource/qss/flatwhite/checkbox_checked.png \
#    $$PWD/resource/qss/flatwhite/checkbox_checked_disable.png \
#    $$PWD/resource/qss/flatwhite/checkbox_parcial.png \
#    $$PWD/resource/qss/flatwhite/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/flatwhite/checkbox_unchecked.png \
#    $$PWD/resource/qss/flatwhite/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/flatwhite/radiobutton_checked.png \
#    $$PWD/resource/qss/flatwhite/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/flatwhite/radiobutton_unchecked.png \
#    $$PWD/resource/qss/flatwhite/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/gray.css \
#    $$PWD/resource/qss/gray/add_bottom.png \
#    $$PWD/resource/qss/gray/add_left.png \
#    $$PWD/resource/qss/gray/add_right.png \
#    $$PWD/resource/qss/gray/add_top.png \
#    $$PWD/resource/qss/gray/branch_close.png \
#    $$PWD/resource/qss/gray/branch_open.png \
#    $$PWD/resource/qss/gray/calendar_nextmonth.png \
#    $$PWD/resource/qss/gray/calendar_prevmonth.png \
#    $$PWD/resource/qss/gray/checkbox_checked.png \
#    $$PWD/resource/qss/gray/checkbox_checked_disable.png \
#    $$PWD/resource/qss/gray/checkbox_parcial.png \
#    $$PWD/resource/qss/gray/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/gray/checkbox_unchecked.png \
#    $$PWD/resource/qss/gray/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/gray/radiobutton_checked.png \
#    $$PWD/resource/qss/gray/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/gray/radiobutton_unchecked.png \
#    $$PWD/resource/qss/gray/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/lightblack.css \
#    $$PWD/resource/qss/lightblack/add_bottom.png \
#    $$PWD/resource/qss/lightblack/add_left.png \
#    $$PWD/resource/qss/lightblack/add_right.png \
#    $$PWD/resource/qss/lightblack/add_top.png \
#    $$PWD/resource/qss/lightblack/branch_close.png \
#    $$PWD/resource/qss/lightblack/branch_open.png \
#    $$PWD/resource/qss/lightblack/calendar_nextmonth.png \
#    $$PWD/resource/qss/lightblack/calendar_prevmonth.png \
#    $$PWD/resource/qss/lightblack/checkbox_checked.png \
#    $$PWD/resource/qss/lightblack/checkbox_checked_disable.png \
#    $$PWD/resource/qss/lightblack/checkbox_parcial.png \
#    $$PWD/resource/qss/lightblack/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/lightblack/checkbox_unchecked.png \
#    $$PWD/resource/qss/lightblack/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/lightblack/radiobutton_checked.png \
#    $$PWD/resource/qss/lightblack/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/lightblack/radiobutton_unchecked.png \
#    $$PWD/resource/qss/lightblack/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/lightblue.css \
#    $$PWD/resource/qss/lightblue/add_bottom.png \
#    $$PWD/resource/qss/lightblue/add_left.png \
#    $$PWD/resource/qss/lightblue/add_right.png \
#    $$PWD/resource/qss/lightblue/add_top.png \
#    $$PWD/resource/qss/lightblue/branch_close.png \
#    $$PWD/resource/qss/lightblue/branch_open.png \
#    $$PWD/resource/qss/lightblue/calendar_nextmonth.png \
#    $$PWD/resource/qss/lightblue/calendar_prevmonth.png \
#    $$PWD/resource/qss/lightblue/checkbox_checked.png \
#    $$PWD/resource/qss/lightblue/checkbox_checked_disable.png \
#    $$PWD/resource/qss/lightblue/checkbox_parcial.png \
#    $$PWD/resource/qss/lightblue/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/lightblue/checkbox_unchecked.png \
#    $$PWD/resource/qss/lightblue/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/lightblue/radiobutton_checked.png \
#    $$PWD/resource/qss/lightblue/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/lightblue/radiobutton_unchecked.png \
#    $$PWD/resource/qss/lightblue/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/lightgray.css \
#    $$PWD/resource/qss/lightgray/add_bottom.png \
#    $$PWD/resource/qss/lightgray/add_left.png \
#    $$PWD/resource/qss/lightgray/add_right.png \
#    $$PWD/resource/qss/lightgray/add_top.png \
#    $$PWD/resource/qss/lightgray/branch_close.png \
#    $$PWD/resource/qss/lightgray/branch_open.png \
#    $$PWD/resource/qss/lightgray/calendar_nextmonth.png \
#    $$PWD/resource/qss/lightgray/calendar_prevmonth.png \
#    $$PWD/resource/qss/lightgray/checkbox_checked.png \
#    $$PWD/resource/qss/lightgray/checkbox_checked_disable.png \
#    $$PWD/resource/qss/lightgray/checkbox_parcial.png \
#    $$PWD/resource/qss/lightgray/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/lightgray/checkbox_unchecked.png \
#    $$PWD/resource/qss/lightgray/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/lightgray/radiobutton_checked.png \
#    $$PWD/resource/qss/lightgray/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/lightgray/radiobutton_unchecked.png \
#    $$PWD/resource/qss/lightgray/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/psblack.css \
#    $$PWD/resource/qss/psblack/add_bottom.png \
#    $$PWD/resource/qss/psblack/add_left.png \
#    $$PWD/resource/qss/psblack/add_right.png \
#    $$PWD/resource/qss/psblack/add_top.png \
#    $$PWD/resource/qss/psblack/branch_close.png \
#    $$PWD/resource/qss/psblack/branch_open.png \
#    $$PWD/resource/qss/psblack/calendar_nextmonth.png \
#    $$PWD/resource/qss/psblack/calendar_prevmonth.png \
#    $$PWD/resource/qss/psblack/checkbox_checked.png \
#    $$PWD/resource/qss/psblack/checkbox_checked_disable.png \
#    $$PWD/resource/qss/psblack/checkbox_parcial.png \
#    $$PWD/resource/qss/psblack/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/psblack/checkbox_unchecked.png \
#    $$PWD/resource/qss/psblack/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/psblack/radiobutton_checked.png \
#    $$PWD/resource/qss/psblack/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/psblack/radiobutton_unchecked.png \
#    $$PWD/resource/qss/psblack/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/silvery.css \
#    $$PWD/resource/qss/silvery/add_bottom.png \
#    $$PWD/resource/qss/silvery/add_left.png \
#    $$PWD/resource/qss/silvery/add_right.png \
#    $$PWD/resource/qss/silvery/add_top.png \
#    $$PWD/resource/qss/silvery/branch_close.png \
#    $$PWD/resource/qss/silvery/branch_open.png \
#    $$PWD/resource/qss/silvery/calendar_nextmonth.png \
#    $$PWD/resource/qss/silvery/calendar_prevmonth.png \
#    $$PWD/resource/qss/silvery/checkbox_checked.png \
#    $$PWD/resource/qss/silvery/checkbox_checked_disable.png \
#    $$PWD/resource/qss/silvery/checkbox_parcial.png \
#    $$PWD/resource/qss/silvery/checkbox_parcial_disable.png \
#    $$PWD/resource/qss/silvery/checkbox_unchecked.png \
#    $$PWD/resource/qss/silvery/checkbox_unchecked_disable.png \
#    $$PWD/resource/qss/silvery/radiobutton_checked.png \
#    $$PWD/resource/qss/silvery/radiobutton_checked_disable.png \
#    $$PWD/resource/qss/silvery/radiobutton_unchecked.png \
#    $$PWD/resource/qss/silvery/radiobutton_unchecked_disable.png \
#    $$PWD/resource/qss/stylesheet.qss \
#    $$PWD/resource/qss/stylesheet/about_hover.png \
#    $$PWD/resource/qss/stylesheet/about_normal.png \
#    $$PWD/resource/qss/stylesheet/banna/1.jpg \
#    $$PWD/resource/qss/stylesheet/banna/2.jpg \
#    $$PWD/resource/qss/stylesheet/banna/3.jpg \
#    $$PWD/resource/qss/stylesheet/banna/4.jpg \
#    $$PWD/resource/qss/stylesheet/banna/5.jpg \
#    $$PWD/resource/qss/stylesheet/close_hover.png \
#    $$PWD/resource/qss/stylesheet/close_normal.png \
#    $$PWD/resource/qss/stylesheet/image.png \
#    $$PWD/resource/qss/stylesheet/left_arrow_hover.png \
#    $$PWD/resource/qss/stylesheet/left_arrow_normal.png \
#    $$PWD/resource/qss/stylesheet/left_arrow_pressed.png \
#    $$PWD/resource/qss/stylesheet/max_hover.png \
#    $$PWD/resource/qss/stylesheet/max_normal.png \
#    $$PWD/resource/qss/stylesheet/min_hover.png \
#    $$PWD/resource/qss/stylesheet/min_normal.png \
#    $$PWD/resource/qss/stylesheet/normal_hover.png \
#    $$PWD/resource/qss/stylesheet/normal_normal.png \
#    $$PWD/resource/qss/stylesheet/other/center_cyan.png \
#    $$PWD/resource/qss/stylesheet/other/circle.png \
#    $$PWD/resource/qss/stylesheet/other/close.png \
#    $$PWD/resource/qss/stylesheet/other/half_star.png \
#    $$PWD/resource/qss/stylesheet/other/hover_blue.png \
#    $$PWD/resource/qss/stylesheet/other/less_than.png \
#    $$PWD/resource/qss/stylesheet/other/more_than.png \
#    $$PWD/resource/qss/stylesheet/other/normal_gray.png \
#    $$PWD/resource/qss/stylesheet/other/splash.png \
#    $$PWD/resource/qss/stylesheet/other/star.png \
#    $$PWD/resource/qss/stylesheet/right_arrow_hover.png \
#    $$PWD/resource/qss/stylesheet/right_arrow_normal.png \
#    $$PWD/resource/qss/stylesheet/right_arrow_pressed.png \
#    $$PWD/resource/web_ui/css/comon0.css \
#    $$PWD/resource/web_ui/css/comon0.css.bak \
#    $$PWD/resource/web_ui/images/bg.jpg \
#    $$PWD/resource/web_ui/images/bg02big2index.png \
#    $$PWD/resource/web_ui/images/bg02bigindex.png \
#    $$PWD/resource/web_ui/images/bg02bigindex_.png \
#    $$PWD/resource/web_ui/images/bg03bigindex.png \
#    $$PWD/resource/web_ui/images/bg04bigindex.png \
#    $$PWD/resource/web_ui/images/head.jpg \
#    $$PWD/resource/web_ui/images/head_bg.png \
#    $$PWD/resource/web_ui/images/jt.png \
#    $$PWD/resource/web_ui/images/jzxz1.png \
#    $$PWD/resource/web_ui/images/jzxz2.png \
#    $$PWD/resource/web_ui/images/lbx.png \
#    $$PWD/resource/web_ui/images/line.png \
#    $$PWD/resource/web_ui/images/loading.gif \
#    $$PWD/resource/web_ui/images/logo.png \
#    $$PWD/resource/web_ui/images/map.png \
#    $$PWD/resource/web_ui/images/weather.png \
#    $$PWD/resource/web_ui/index.html \
#    $$PWD/resource/web_ui/js/area_echarts.js \
#    $$PWD/resource/web_ui/js/bmap.js \
#    $$PWD/resource/web_ui/js/china.js \
#    $$PWD/resource/web_ui/js/common.js \
#    $$PWD/resource/web_ui/js/common.js.bak \
#    $$PWD/resource/web_ui/js/echarts-gl.js \
#    $$PWD/resource/web_ui/js/echarts-gl.min.js \
#    $$PWD/resource/web_ui/js/echarts-tool.js \
#    $$PWD/resource/web_ui/js/echarts-tool.js.bak \
#    $$PWD/resource/web_ui/js/echarts-tool1.js \
#    $$PWD/resource/web_ui/js/echarts.all.js \
#    $$PWD/resource/web_ui/js/echarts.blank.js \
#    $$PWD/resource/web_ui/js/echarts.common.js \
#    $$PWD/resource/web_ui/js/echarts.common.min.js \
#    $$PWD/resource/web_ui/js/echarts.js \
#    $$PWD/resource/web_ui/js/echarts.js.map \
#    $$PWD/resource/web_ui/js/echarts.min.js \
#    $$PWD/resource/web_ui/js/echarts.simple.js \
#    $$PWD/resource/web_ui/js/echarts.simple.min.js \
#    $$PWD/resource/web_ui/js/jquery.countup.min.js \
#    $$PWD/resource/web_ui/js/jquery.js \
#    $$PWD/resource/web_ui/js/jquery.waypoints.min.js \
#    $$PWD/resource/web_ui/js/pointcloud.js \
#    $$PWD/resource/web_ui/js/qwebchannel.js \
#    $$PWD/resource/web_ui/js/timelineOption.js
