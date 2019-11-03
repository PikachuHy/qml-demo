include_directories("../lib")
add_executable(sdate2idate_test test.c sdate2idate_test.c ../lib/util.c)
add_executable(ReadOrderTable_test ReadOrderTable_test.c test.c)
target_link_libraries(ReadOrderTable_test df347)
add_executable(ReadCustomerTable_test ReadCustomerTable_test.c test.c)
target_link_libraries(ReadCustomerTable_test df347)

add_executable(CreateCustomerIndex_test CreateCustomerIndex_test.c test.c)
target_link_libraries(CreateCustomerIndex_test df347)

add_executable(list_test list_test.c test.c)
target_link_libraries(list_test df347)

add_executable(hashmap_test hashmap_test.c test.c)
target_link_libraries(hashmap_test df347)

add_executable(priorityqueue_test priorityqueue_test.c test.c)
target_link_libraries(priorityqueue_test df347)

add_executable(RecordMinHeap_test RecordMinHeap_test.c test.c)
target_link_libraries(RecordMinHeap_test df347)

add_executable(ParseQueryParam_test ParseQueryParam_test.c test.c)
target_link_libraries(ParseQueryParam_test df347)