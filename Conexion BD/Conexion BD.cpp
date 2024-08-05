#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>


using namespace std;

int main() {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;

    // Asignar un gestor de entorno
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    // Asignar un gestor de conexión
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Conectarse a la base de datos
    ret = SQLConnect(hDbc, (SQLWCHAR*)L"sqlserver", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "Conectado a la base de datos exitosamente." << endl;

                // Ejemplo de ejecución de una consulta
        SQLHSTMT hStmt;
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

            // Liberar el manejador de conexión
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        }
        else {
            cout << "Fallo la conexion a la base de datos" << endl;
        }

        // Desconectar y liberar gestores de entorno
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

        return 0;
    }
