#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>

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

        // Imprimir encabezados de la tabla
        cout << "+--------------+----------------------------+------------+------------+-------------------+----------------------+------------------------------+-----------+" << endl;
        cout << "| Num_Empleado | Nombre Completo            | Fecha_Nac  | RFC        | C_trabajo         | Puesto               | Des_Puesto                   | Directivo |" << endl;
        cout << "+--------------+----------------------------+------------+------------+-------------------+----------------------+------------------------------+-----------+" << endl;
        
        // Ejemplo de consulta SELECT
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Datos_Empleados", SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            int num_empleado;
            SQLCHAR name[50];
            SQLCHAR last_name[50];
            SQLCHAR slast_name[50];
            SQLCHAR fecha_n[50];
            SQLCHAR rfc[50];
            SQLCHAR c_trabajo[50];
            SQLCHAR puesto[50];
            SQLCHAR desc_puesto[50];
            SQLCHAR directivo[50];
            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_LONG, &num_empleado, 0, NULL);
                SQLGetData(hStmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);
                SQLGetData(hStmt, 3, SQL_C_CHAR, last_name, sizeof(last_name), NULL);
                SQLGetData(hStmt, 4, SQL_C_CHAR, slast_name, sizeof(slast_name), NULL);
                SQLGetData(hStmt, 5, SQL_C_CHAR, fecha_n, sizeof(fecha_n), NULL);
                SQLGetData(hStmt, 6, SQL_C_CHAR, rfc, sizeof(rfc), NULL);
                SQLGetData(hStmt, 7, SQL_C_CHAR, c_trabajo, sizeof(c_trabajo), NULL);
                SQLGetData(hStmt, 8, SQL_C_CHAR, puesto, sizeof(puesto), NULL);
                SQLGetData(hStmt, 9, SQL_C_CHAR, desc_puesto, sizeof(desc_puesto), NULL);
                SQLGetData(hStmt, 10, SQL_C_CHAR, directivo, sizeof(directivo), NULL);

                // Concatenar nombre y apellido paterno
                string last_names = string((char*)last_name) + " " + string((char*)slast_name);
                string full_name = string((char*)name) + " " + string(last_names);
               
                //Convertir BIT a String
                string dir = string((char*)directivo);
                string respuesta;

                if (dir == "1") {
                    respuesta = "SI";
                }
                else
                {
                    respuesta = "NO";
                }
                
                // Imprimir datos de la fila con alineación
                cout << "| " << setw(13) << left << num_empleado
                     << "| " << setw(27) << left << full_name
                     << "| " << setw(11) << left << fecha_n
                     << "| " << setw(11) << left << rfc
                     << "| " << setw(18) << left << c_trabajo
                     << "| " << setw(21) << left << puesto
                     << "| " << setw(29) << left << desc_puesto
                     << "| " << setw(9) << left << respuesta << " |" << endl;
                

                //cout <<"|" <<num_empleado << "              | " << name << "     | " << last_name << "  |   " << slast_name << " |  " << fecha_n << " | " << rfc << "  | " << c_trabajo << "    | " << puesto << " | " << desc_puesto << " | " << directivo << endl;
                cout << "+--------------+----------------------------+------------+------------+-------------------+----------------------+------------------------------+-----------+" << endl;
            }
        }

        // Liberar el manejador de conexión
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Asignar un gestor de entorno
        ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
        ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

        // Asignar un gestor de conexión
        ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

        ret = SQLConnect(hDbc, (SQLWCHAR*)L"sqlserver", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);

        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            cout << "Conectado a la base de datos exitosamente." << endl;

            // Ejemplo de ejecución de una consulta
            SQLHSTMT hStmt;
            ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

            // Imprimir encabezados de la tabla
            cout << "+--------------+------------+------------------------+" << endl;
            cout << "| No. Empleado | No. Centro | Prestacion Combustible |" << endl;
            cout << "+--------------+------------+------------------------+" << endl;        

            // Ejemplo de consulta SELECT
            ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Datos_Directivos", SQL_NTS);
            if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
                int num_empleado;
                int num_centro;
                SQLCHAR prestacion_gasolina[50];
               
                while (SQLFetch(hStmt) == SQL_SUCCESS) {
                    SQLGetData(hStmt, 1, SQL_C_LONG, &num_empleado, 0, NULL);
                    SQLGetData(hStmt, 2, SQL_C_LONG, &num_centro, 0, NULL);
                    SQLGetData(hStmt, 3, SQL_C_CHAR, prestacion_gasolina, sizeof(prestacion_gasolina), NULL);

                    //Convertir BIT a String
                    string p_gas = string((char*)prestacion_gasolina);
                    string respuesta2;

                    if (p_gas == "1") {
                        respuesta2 = "SI";
                    }
                    else
                    {
                        respuesta2 = "NO";
                    }

                    // Imprimir datos de la fila con alineación
                    cout << "| " << setw(13) << left << num_empleado
                         << "| " << setw(11) << left << num_centro
                         << "| " << setw(22) << left << respuesta2 << " |" << endl;

                   // cout << "| " << num_empleado  << "             | " << num_centro << "        | " << prestacion_gasolina << "                       | " << endl;
                    cout << "+--------------+------------+------------------------+" << endl;
                }
            }

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
}
