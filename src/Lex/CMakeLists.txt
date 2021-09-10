set(DIR "${CMAKE_SOURCE_DIR}/Lex/")

#使用reflex必须设置的
#add_link_options(-lreflex)
#在cmake生成make期间执行
execute_process(COMMAND reflex --yy -o ${DIR}lexer.cpp ${DIR}lexer.l)

#add_custom_command(OUTPUT lexgen
#    COMMAND reflex --flex --bison -o ${LEXDIR}lexer.cpp ${LEXDIR}lexer.l 
#    )
#    #WORKING_DIRECTORY ${LEXDIR}

#make时重新根据是否修改.l文件再次编译，make clean可以删除生成文件
add_custom_target(lex ALL
    COMMAND reflex --yy -o ${DIR}lexer.cpp ${DIR}lexer.l
    DEPENDS ${DIR}lexer.l
    BYPRODUCTS ${DIR}lexer.cpp
    )

