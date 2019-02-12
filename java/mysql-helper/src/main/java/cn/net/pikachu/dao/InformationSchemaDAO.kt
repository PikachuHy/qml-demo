package cn.net.pikachu.dao

import cn.net.pikachu.model.Column
import cn.net.pikachu.model.Table
import cn.net.pikachu.model.View
import java.sql.Connection
import java.sql.DriverManager

object InformationSchemaDAO {
    private val connection: Connection by lazy {
        Class.forName("com.mysql.cj.jdbc.Driver")
        val url = "jdbc:mysql://127.0.0.1:3306/information_schema?useUnicode=true&characterEncoding=utf-8&serverTimezone=UTC&verifyServerCertificate=false&useSSL=false"
        DriverManager.getConnection(url, "root", "root")
    }

    fun getTableList(dbName: String): List<Table> {
        val prepareStatement = connection.prepareStatement("select * from tables where table_schema = ? and table_type = 'BASE TABLE'")
        prepareStatement.setString(1, dbName)
        val resultSet = prepareStatement.executeQuery()
        val list = ArrayList<Table>()
        while (resultSet.next()) {
            val table = Table().apply {
                with(resultSet) {
                    tableName = getString("table_name")
                    engine = getString("engine")
                    tableComment = getString("table_comment")
                    tableCollation = getString("table_collation")
                }
            }
            list.add(table)
        }
        return list
    }

    fun getTableColumnList(dbName: String, tableName: String): List<Column> {
        val prepareStatement = connection.prepareStatement("select * from columns where table_schema = ? and table_name = ?")
        prepareStatement.setString(1, dbName)
        prepareStatement.setString(2, tableName)
        val resultSet = prepareStatement.executeQuery()
        val list = ArrayList<Column>()
        while (resultSet.next()) {
            val column = Column().apply {
                with(resultSet) {
                    columnName = getString("column_name")
                    columnType = getString("column_type")
                    dataType = getString("data_type")
                    columnComment = getString("column_comment")
                    extra = getString("extra")
                    columnKey = getString("column_key")
                    columnDefault = getString("column_default")
                    isNullable = getString("is_nullable")
                }
            }
            list.add(column)
        }
        return list
    }

    fun getViewList(dbName: String): List<View> {
        val prepareStatement = connection.prepareStatement("select * from views where table_schema = ?")
        prepareStatement.setString(1, dbName)
        val resultSet = prepareStatement.executeQuery()
        val list = ArrayList<View>()
        while (resultSet.next()) {
            val view = View().apply {
                tableName = resultSet.getString("table_name")
                viewDefinition = resultSet.getString("view_definition")
            }
            list.add(view)
        }
        return list
    }
}
