cmake_minimum_required(VERSION 3.14)

include(cmake/SparkWithGit.cmake)

project(clipboard-history-analyzer LANGUAGES CXX VERSION 0.0.1)

spark_initialize_modules()

# 资源文件路径
set(QRC_SOURCES "res/res.qrc")

spark_add_executable_path(${PROJECT_NAME} 
    src
    src/widgets
    ${QRC_SOURCES}
)
target_link_qt5(${PROJECT_NAME})

spark_framework_include_with_git(${PROJECT_NAME} 
    https://gitee.com/spark-framework-libs/spark-framework-features
    FEATURES version screenutil
)

spark_framework_include_with_git(${PROJECT_NAME}
    https://gitee.com/spark-framework-libs/simple-frameless-libs
    FEATURES frameless
)


# include(cmake/SparkDesktopMacros.cmake)
# 内容默认应用名称: Name= 应与项目名称相同
spark_desktop_macros(
    # 应用名称: Name=
    "Clipboard History Analyzer"
    # 应用名称: Name[zh_CN]=
    "剪贴板历史分析工具"
    # 应用说明: Comment=
    ""
    # 应用类型: Type=
    "Application"
    # 执行程序: Exec=
    "/opt/apps/com.gitee.zinface.clipboard-history-analyzer/bin/clipboard-history-analyzer"
    # 图标路径: Icon=
    "/opt/apps/com.gitee.zinface.clipboard-history-analyzer/icon/icon.png"
    # 应用分类: Categories=
    "Utility"
    # MIME类型: MimeType=
    ""
)

# 安装快捷方式
spark_install_file(/usr/share/applications 
    ${SPARK_DESKTOP_FILE})
# 安装图标
spark_install_file(/opt/apps/com.gitee.zinface.clipboard-history-analyzer/icon 
    res/icon.png)
# 安装目标
spark_install_target(/opt/apps/com.gitee.zinface.clipboard-history-analyzer/bin 
    clipboard-history-analyzer)

add_package_descript(cmake/spark-deb-package.descript)