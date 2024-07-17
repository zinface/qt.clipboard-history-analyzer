cmake_minimum_required(VERSION 3.14)

include(cmake/SparkWithGit.cmake)

project(template LANGUAGES CXX VERSION 0.0.1)

spark_initialize_modules()

# 资源文件路径
set(QRC_SOURCES "")

spark_add_executable_path(${PROJECT_NAME} 
    src
    ${QRC_SOURCES}
)
target_link_qt5(${PROJECT_NAME})

spark_framework_include_with_git(${PROJECT_NAME} 
    https://gitee.com/spark-framework-libs/spark-framework-features
    FEATURES version screenutil)