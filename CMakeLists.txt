cmake_minimum_required(VERSION 3.23)
project(thirdAssignment)

set(CMAKE_CXX_STANDARD 11)

add_executable(thirdAssignment main.cpp ReadAndWriteFile.cpp ReadAndWriteFile.h Model1.cpp Model1.h Model2.cpp Model2.h CashierQueue.cpp CashierQueue.h Order.h Cashier.cpp Cashier.h Barista.cpp Barista.h)
