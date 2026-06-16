#ifndef CLIENTSTYLESHEET_H
#define CLIENTSTYLESHEET_H

#include<QString>

namespace toolFrameStyle {
static QString pauseButtonStytle = "QPushButton {"
                                   "    background-image: url(:/picture/pause.png);"
                                   "    background-repeat: no-repeat;"
                                   "    background-position: center;"
                                   "    border: none;"
                                   "}";

static  QString playButtonStytle = "QPushButton {"
                                   "    background-image: url(:/picture/play.png);"
                                   "    background-repeat: no-repeat;"
                                   "    background-position: center;"
                                   "    border: none;"
                                   "}";

static QString frameStytle= "QFrame{"
                            "border: 1px solid #0056b3;"
                            "border-radius:5px;"
                            "background-color:#ffffff;"
                            "}";

static QString buttonStytle = "QPushButton {"
                              "    background-color: #1296db;"
                              "    color: white;"
                              "    border: transparent;"
                              "    padding: 10px;"
                              "border-radius:10px;"
                              "font:bold 25px;"
                              "}";



static QString videoListButtonStytle = "QPushButton {"
                                       "    background-image: url(:/picture/videoList.png);"
                                       "    background-repeat: no-repeat;"
                                       "    background-position: center;"
                                       "    border: none;"
                                       "}";


static QString prevButtonStytle = "QPushButton {"
                                  "    background-image: url(:/picture/prev.png);"
                                  "    background-repeat: no-repeat;"
                                  "    background-position: center;"
                                  "    border: none;"
                                  "}";

static QString nextButtonStytle = "QPushButton {"
                                  "    background-image: url(:/picture/next.png);"
                                  "    background-repeat: no-repeat;"
                                  "    background-position: center;"
                                  "    border: none;"
                                  "}";

static QString configButtonStytle = "QPushButton {"
                                    "    background-image: url(:/picture/config.png);"
                                    "    background-repeat: no-repeat;"
                                    "    background-position: center;"
                                    "    border: none;"
                                    "}";


static QString smallLabelStytle ="QLabel{"
                                 "font:bold 15px 'Arial';"
                                 "color:#0056b3;"
                                 "border:none;"
                                 "}";

static QString voulmeLabelStytle = "QLabel {"
                                   "    background-image: url(:/picture/volume.png);"
                                   "    background-repeat: no-repeat;"
                                   "    background-position: center;"
                                   "    border: none;"
                                   "}";


static QString speedLabelStytle = "QLabel {"
                                  "    background-image: url(:/picture/speed.png);"
                                  "    background-repeat: no-repeat;"
                                  "    background-position: center;"
                                  "    border: none;"
                                  "}";

static QString scaleLabelStytle = "QLabel {"
                                  "    background-image: url(:/picture/scale.png);"
                                  "    background-repeat: no-repeat;"
                                  "    background-position: center;"
                                  "    border: none;"
                                  "}";


static QString comboBoxStyle = R"(
                               QComboBox {
                               font: bold 25px 'Arial'; /* 字体与 QLabel 保持一致 */
                               color: #0056b3; /* 文字颜色与 QLabel 保持一致 */
                               background-color: #ffffff; /* 背景颜色，可根据需要调整 */
                               border: 2px solid #0056b3; /* 边框颜色与 QLabel 文字颜色一致 */
                               border-radius: 4px; /* 边框圆角 */
                               padding: 5px; /* 内边距 */
                               }

                               QComboBox::drop-down {
                               subcontrol-origin: padding;
                               subcontrol-position: top right;
                               width: 20px;
                               border-left-width: 2px;
                               border-left-color: #0056b3; /* 下拉箭头左边框颜色与 QLabel 文字颜色一致 */
                               border-left-style: solid;
                               border-top-right-radius: 4px;
                               border-bottom-right-radius: 4px;
                               background-color: #e0e0e0;
                               }

                               QComboBox::down-arrow {
                               image: url(arrow_down.png); /* 可替换为自定义箭头图标 */
                               width: 12px;
                               height: 12px;
                               }

                               QComboBox QAbstractItemView {
                               border: 1px solid #0056b3; /* 下拉列表边框颜色与 QLabel 文字颜色一致 */
                               border-radius: 4px;
                               background-color: #ffffff;
                               selection-background-color: #0056b3; /* 选中项背景颜色与 QLabel 文字颜色一致 */
                               selection-color: #ffffff; /* 选中项文字颜色 */
                               }
                               )";


static QString volumeSliderStyle = R"(
                                   QSlider::groove:horizontal {
                                   border: 1px solid #CCCAFA;
                                   height: 10px;
                                   margin: 0px 0;
                                   left: 2px; right: 2px;
                                   background-color: #CCCAFA;
                                   border-radius: 5px; /* 为轨道设置圆角 */
                                   }

                                   QSlider::sub-page:horizontal {
                                   background-color: #0056b3;
                                   border-radius: 5px; /* 划过部分圆角与轨道保持一致 */
                                   }

                                   QSlider::handle:horizontal {
                                   width: 25px;
                                   height: 25px;
                                   margin: -3px 0;
                                   border: none; /* 去除滑块的边框 */
                                   border-radius: 7.5px;
                                   background-color: #CCCAFF; /* 设置滑块的背景颜色 */
                                   }
                                   )";

}

namespace configurationStyle {
static QString labelStytle ="QLabel{"
                            "font:bold 40px 'Arial';"
                            "color:#0056b3;"
                            "}";

static QString smallLabelStytle ="QLabel{"
                                 "font:bold 20px 'Arial';"
                                 "color:#0056b3;"
                                 "}";


static QString checkBoxStyle = R"(
                               QCheckBox {
                               font: bold 20px 'Arial';
                               color: #0056b3;
                               padding: 5px;
                               }
                               QCheckBox::indicator {
                               width: 25px;
                               height: 25px;
                               border: 2px solid #0056b3;
                               border-radius: 8px;
                               background-color: #fff;
                               }
                               QCheckBox::indicator:hover {
                               border-color: #0056b3;
                               }
                               QCheckBox::indicator:checked {
                               background-color: #0056b3;
                               border-color: #0056b3;
                               }
                               )";



static QString sliderStyle = R"(
                             QSlider::groove:horizontal {
                             border: 1px solid #CCCAFA;
                             height: 10px;
                             margin: 0px 0;
                             left: 2px; right: 2px;
                             background-color: #CCCAFA;
                             border-radius: 5px; /* 为轨道设置圆角 */
                             }

                             QSlider::sub-page:horizontal {
                             background-color: #0056b3;
                             border-radius: 5px; /* 划过部分圆角与轨道保持一致 */
                             }

                             QSlider::handle:horizontal {
                             width: 25px;
                             height: 25px;
                             margin: -3px 0;
                             border: none; /* 去除滑块的边框 */
                             border-radius: 7.5px;
                             background-color: #CCCAFF; /* 设置滑块的背景颜色 */
                             }
                             )";
}

namespace nativeWidgetStyle {
static QString frameStytle= "QFrame{"
                            "border: 1px solid #0056b3;"
                            "border-radius:5px;"
                            "background-color:#ffffff;"
                            "}";


static QString addVideoStyle = "QPushButton {"
                               "    background-image: url(:/picture/addVideo.png);"
                               "    background-repeat: no-repeat;"
                               "    background-position: center;"
                               "    border: none;"
                               "}";
static QString deleteVideoStyle = "QPushButton {"
                                  "    background-image: url(:/picture/deleteVideo.png);"
                                  "    background-repeat: no-repeat;"
                                  "    background-position: center;"
                                  "    border: none;"
                                  "}";


static QString labelStytle ="QLabel{"
                            "font:bold 40px 'Arial';"
                            "color:#0056b3;"
                            "border:none;"
                            "}";

static QString smallLabelStytle ="QLabel{"
                                 "font:bold 25px 'Arial';"
                                 "color:#0056b3;"
                                 "border:none;"
                                 "}";

static QString onListLabelStyle = "QLabel{"
                                  "font:bold 20px 'Arial';"
                                  "color:#0056b3;"
                                  "border:none;"
                                  "background:transparent;"
                                  "}";


static QString checkBoxStyle = R"(
                               QCheckBox {
                               font: bold 25px 'Arial';
                               color: #0056b3;
                               padding: 5px;
                               }
                               QCheckBox::indicator {
                               width: 25px;
                               height: 25px;
                               border: 2px solid #0056b3;
                               border-radius: 8px;
                               background-color: #fff;
                               }
                               QCheckBox::indicator:hover {
                               border-color: #0056b3;
                               }
                               QCheckBox::indicator:checked {
                               background-color: #0056b3;
                               border-color: #0056b3;
                               }
                               )";

static QString recordCheckBoxStyle=R"(
                                   QCheckBox {
                                   font: bold 15px 'Arial';
                                   color: #0056b3;
                                   padding: 5px;
                                   }
                                   QCheckBox::indicator {
                                   width: 25px;
                                   height: 25px;
                                   border: 2px solid #0056b3;
                                   border-radius: 8px;
                                   background-color: #fff;
                                   }
                                   QCheckBox::indicator:hover {
                                   border-color: #0056b3;
                                   }
                                   QCheckBox::indicator:checked {
                                   background-color: #0056b3;
                                   border-color: #0056b3;
                                   }
                                   )";


static QString comboBoxStyle = R"(
                               QComboBox {
                               font: bold 25px 'Arial'; /* 字体与 QLabel 保持一致 */
                               color: #0056b3; /* 文字颜色与 QLabel 保持一致 */
                               background-color: #ffffff; /* 背景颜色，可根据需要调整 */
                               border: 2px solid #0056b3; /* 边框颜色与 QLabel 文字颜色一致 */
                               border-radius: 4px; /* 边框圆角 */
                               padding: 5px; /* 内边距 */
                               }

                               QComboBox::drop-down {
                               subcontrol-origin: padding;
                               subcontrol-position: top right;
                               width: 20px;
                               border-left-width: 2px;
                               border-left-color: #0056b3; /* 下拉箭头左边框颜色与 QLabel 文字颜色一致 */
                               border-left-style: solid;
                               border-top-right-radius: 4px;
                               border-bottom-right-radius: 4px;
                               background-color: #0056b3;
                               }

                               QComboBox::down-arrow {
                               width: 12px;
                               height: 12px;
                               }

                               QComboBox QAbstractItemView {
                               border: 1px solid #0056b3; /* 下拉列表边框颜色与 QLabel 文字颜色一致 */
                               border-radius: 4px;
                               background-color: #ffffff;
                               selection-background-color: #0056b3; /* 选中项背景颜色与 QLabel 文字颜色一致 */
                               selection-color: #ffffff; /* 选中项文字颜色 */
                               }
                               )";



static QString listViewStyle = R"(
                               QListView {
                               font: bold 20px 'Arial'; /* 字体与 QLabel 保持一致 */
                               color: #0056b3; /* 文字颜色与 QLabel 保持一致 */
                               background-color: #ffffff; /* 背景颜色 */
                               border: none; /* 边框颜色与 QLabel 文字颜色一致 */
                               padding: 5px; /* 内边距 */
                               }

                               QListView::item {
                               padding: 5px; /* 列表项内边距 */
                               }

                               QListView::item:selected{
                               background-color: #0056b3; /* 选中项背景颜色与 QLabel 文字颜色一致 */
                               color: #ffffff; /* 选中项文字颜色 */
                               }

                               QListView::item:hover {
                               background-color: #CCCCFF; /* 鼠标悬停时列表项背景颜色 */
                               }
                               QListView::item:focus{
                               outline:none;
                               }
                               )";

static QString scrollAreaStyle = R"(
                                 QScrollArea {
                                 border: 1px solid #0056b3; /* 边框颜色与 QLabel 文字颜色一致 */
                                 border-radius: 5px; /* 边框圆角 */
                                 background-color: #ffffff; /* 背景颜色 */
                                 }

                                 QScrollBar:vertical {
                                 border: none;
                                 background: #ffffff;
                                 width: 10px;
                                 margin: 0px 0px 0px 0px;
                                 }

                                 QScrollBar::handle:vertical {
                                 background: #0056b3; /* 滚动条滑块颜色与 QLabel 文字颜色一致 */
                                 min-height: 20px;
                                 border-radius: 5px;
                                 }

                                 QScrollBar::add-line:vertical,
                                 QScrollBar::sub-line:vertical {
                                 height: 0px;
                                 subcontrol-position: bottom;
                                 subcontrol-origin: margin;
                                 }

                                 QScrollBar::add-page:vertical,
                                 QScrollBar::sub-page:vertical {
                                 background: none;
                                 }

                                 QScrollBar:horizontal {
                                 border: none;
                                 background: #ffffff;
                                 height: 10px;
                                 margin: 0px 0px 0px 0px;
                                 }

                                 QScrollBar::handle:horizontal {
                                 background: #0056b3; /* 滚动条滑块颜色与 QLabel 文字颜色一致 */
                                 min-width: 20px;
                                 border-radius: 5px;
                                 }

                                 QScrollBar::add-line:horizontal,
                                 QScrollBar::sub-line:horizontal {
                                 width: 0px;
                                 subcontrol-position: right;
                                 subcontrol-origin: margin;
                                 }

                                 QScrollBar::add-page:horizontal,
                                 QScrollBar::sub-page:horizontal {
                                 background: none;
                                 }
                                 )";


static QString videoSliderStyle = R"(
                                  QSlider::groove:horizontal {
                                  border: 1px solid #CCCAFA;
                                  height: 10px;
                                  margin: 0px 0;
                                  left: 2px; right: 2px;
                                  background-color: #CCCAFA;
                                  border-radius: 5px; /* 为轨道设置圆角 */
                                  }

                                  QSlider::sub-page:horizontal {
                                  background-color: #0056b3;
                                  border-radius: 5px; /* 划过部分圆角与轨道保持一致 */
                                  }

                                  QSlider::handle:horizontal {
                                  width: 25px;
                                  height: 25px;
                                  margin: -3px 0;
                                  border: none; /* 去除滑块的边框 */
                                  border-radius: 7.5px;
                                  background-color: #CCCAFF; /* 设置滑块的背景颜色 */
                                  }
                                  )";
}

namespace modifyPasswordWidgetStyle{
static QString lineEditStyle = "QLineEdit {"
                               "    background-color: white;"
                               "    color: #333;"
                               "    border: 1px solid #ccc;"
                               "    border-radius: 4px;"
                               "    padding: 5px;"
                               "}"
                               "QLineEdit:focus {"
                               "    border: 1px solid #007BFF;"
                               "    outline: none;"
                               "}"
                               "QLineEdit:disabled {"
                               "    background-color: #e9e9e9;"
                               "    color: #999;"
                               "    border: 1px solid #bbb;"
                               "}"
                               "QLineEdit::placeholder {"
                               "    color: #999;"
                               "}";



static QString buttonStytle = "QPushButton {"
                              "    background-color: #007BFF;"
                              "    color: white;"
                              "    border: transparent;"
                              "    padding: 10px;"
                              "border-radius:10px;"
                              "font:20px;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #0056b3;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #003d80;"
                              "}";


static QString labelStytle ="QLabel{"
                            "font:bold 25px 'Arial';"
                            "color:#0056b3;"
                            "}";

static QString labelStytle2 ="QLabel{"
                             "    font: italic bold 60px 'Arial';"
                             "color:#003d80;"
                             "}";
}

namespace registerWidgetStyle {
static QString lineEditStyle = "QLineEdit {"
                               "    background-color: white;"
                               "    color: #333;"
                               "    border: 1px solid #ccc;"
                               "    border-radius: 4px;"
                               "    padding: 5px;"
                               "}"
                               "QLineEdit:focus {"
                               "    border: 1px solid #007BFF;"
                               "    outline: none;"
                               "}"
                               "QLineEdit:disabled {"
                               "    background-color: #e9e9e9;"
                               "    color: #999;"
                               "    border: 1px solid #bbb;"
                               "}"
                               "QLineEdit::placeholder {"
                               "    color: #999;"
                               "}";

static QString buttonStytle = "QPushButton {"
                              "    background-color: #007BFF;"
                              "    color: white;"
                              "    border: transparent;"
                              "    padding: 10px;"
                              "border-radius:10px;"
                              "font:20px;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #0056b3;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #003d80;"
                              "}";

static QString labelStytle ="QLabel{"
                            "font:bold 25px 'Arial';"
                            "color:#0056b3;"
                            "}";


static QString labelStytle2 ="QLabel{"
                             "    font: italic bold 60px 'Arial';"
                             "color:#003d80;"
                             "}";
}

namespace loginWidgetStyle{

static QString lineEditStyle = "QLineEdit {"
                               "    background-color: white;"
                               "    color: #333;"
                               "    border: 1px solid #ccc;"
                               "    border-radius: 4px;"
                               "    padding: 5px;"
                               "}"
                               "QLineEdit:focus {"
                               "    border: 1px solid #007BFF;"
                               "    outline: none;"
                               "}"
                               "QLineEdit:disabled {"
                               "    background-color: #e9e9e9;"
                               "    color: #999;"
                               "    border: 1px solid #bbb;"
                               "}"
                               "QLineEdit::placeholder {"
                               "    color: #999;"
                               "}";

static QString buttonStytle = "QPushButton {"
                              "    background-color: #007BFF;"
                              "    color: white;"
                              "    border: transparent;"
                              "    padding: 10px;"
                              "border-radius:10px;"
                              "font:20px;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #0056b3;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #003d80;"
                              "}";

static QString labelStytle ="QLabel{"
                            "font:bold 25px 'Arial';"
                            "color:#0056b3;"
                            "}";


static QString labelStytle2 ="QLabel{"
                             "    font: italic bold 60px 'Arial';"
                             "color:#003d80;"
                             "}";
}

namespace userHeadWidgetStyle {
static QString lineEditStyle = "QLineEdit {"
                               "    background-color: transparent;"
                               "    color: #333;"
                               "    border: 1px solid #ccc;"
                               "    border-radius: 4px;"
                               "    padding: 5px;"
                               "    font-family: 'Microsoft YaHei'; /* 设置字体类型 */"
                               "    font-size: 14px; /* 设置字体大小 */"
                               "    font-weight: normal; /* 设置字体正常粗细 */"
                               "}"
                               "QLineEdit:focus {"
                               "    border: 1px solid #007BFF;"
                               "    outline: none;"
                               "}"
                               "QLineEdit:disabled {"
                               "    background-color: transparent;"
                               "    border: none;"
                               "}"
                               "QLineEdit::placeholder {"
                               "    color: #999;"
                               "}";

static QString lineEditStyle2 = "QLineEdit {"
                                "    background-color: transparent;"
                                "    color: #0056b3;"
                                "    border: 1px solid #ccc;"
                                "    border-radius: 4px;"
                                "    padding: 5px;"
                                "    font-family: 'Microsoft YaHei'; /* 设置字体类型 */"
                                "    font-size: 20px; /* 设置字体大小 */"
                                "    font-weight: bold; /* 设置字体加粗 */"
                                "}"
                                "QLineEdit:focus {"
                                "    border: 1px solid #007BFF;"
                                "    outline: none;"
                                "}"
                                "QLineEdit:disabled {"
                                "    background-color: transparent;"
                                "    border: none;"
                                "}"
                                "QLineEdit::placeholder {"
                                "    color: #999;"
                                "}";

static QString buttonStytle = "QPushButton {"
                              "    background-color: #007BFF;"
                              "    color: white;"
                              "    border: transparent;"
                              "    padding: 10px;"
                              "border-radius:10px;"
                              "font:20px;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #0056b3;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #003d80;"
                              "}";


static QString labelStytle ="QLabel{"
                            "font:bold 25px 'Arial';"
                            "color:#0056b3;"
                            "}";
}

namespace userWidgetStyle {
static QString lineEditStyle = "QLineEdit {"
                               "    background-color: transparent;"
                               "    color: #333;"
                               "    border: 1px solid #ccc;"
                               "    border-radius: 4px;"
                               "    padding: 5px;"
                               "    font-family: 'Microsoft YaHei'; /* 设置字体类型 */"
                               "    font-size: 14px; /* 设置字体大小 */"
                               "}"
                               "QLineEdit:focus {"
                               "    border: 1px solid #007BFF;"
                               "    outline: none;"
                               "}"
                               "QLineEdit:disabled {"
                               "    background-color: transparent;"
                               "    border: none;"
                               "}"
                               "QLineEdit::placeholder {"
                               "    color: #999;"
                               "}";

static QString buttonStytle = "QPushButton {"
                              "    background-color: #007BFF;"
                              "    color: white;"
                              "    border: transparent;"
                              "    padding: 10px;"
                              "border-radius:10px;"
                              "font:20px;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #0056b3;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #003d80;"
                              "}";




static QString labelStytle ="QLabel{"
                            "font:bold 25px 'Arial';"
                            "color:#0056b3;"
                            "}";


static QString checkBoxStyle = R"(
                               QCheckBox {
                               font: 15px 'Arial' bold ;
                               color: #333;
                               padding: 5px;
                               }
                               QCheckBox::indicator {
                               width: 18px;
                               height: 18px;
                               border: 2px solid #ccc;
                               border-radius: 8px;
                               background-color: #fff;
                               }
                               QCheckBox::indicator:hover {
                               border-color: #999;
                               }
                               QCheckBox::indicator:checked {
                               background-color: red;
                               border-color: red;
                               }
                               )";

static QString radioButtonStyle = R"(
                                  QRadioButton {

                                  font: 20px 'Arial' bold;
                                  color: #333;
                                  padding: 5px;
                                  }
                                  QRadioButton::indicator {
                                  width: 18px;
                                  height: 18px;
                                  border: 2px solid #ccc;
                                  border-radius: 9px;
                                  background-color: #fff;
                                  }
                                  QRadioButton::indicator:hover {
                                  border-color: #999;
                                  }
                                  QRadioButton::indicator:checked {
                                  background-color: red;
                                  border-color: red;

                                  }
                                  )";
}

namespace videoMainWindowStyle {
static QString buttonStytle = "QPushButton {"
                              "background-color: #007BFF;"
                              "color: white;"
                              "border: transparent;"
                              "padding: 10px;"
                              "border-radius:10px;"
                              "font:20px;"
                              "}"
                              "QPushButton:hover {"
                              "background-color: #0056b3;"
                              "font:23px;"
                              "}"
                              "QPushButton:pressed {"
                              "background-color: #003d80;"
                              "font:23px;"
                              "}";

static QString labelStyle = "QLabel {"
                            "background-color: #007BFF;"
                            "color: white;"
                            "border: 1px solid transparent;"
                            "padding: 10px;"
                            "border-radius: 10px;"
                            "font-size: 20px;"
                            "}";
}

#endif // CLIENTSTYLESHEET_H
