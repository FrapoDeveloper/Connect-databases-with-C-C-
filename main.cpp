#include <iostream>
#include <string>
#include <windows.h>
#include <mysql.h>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
using namespace std;

int main()
{
   time_t t;
   struct tm *tm;
   char fecha[10],hora[10],fechayhora[25];
   t=time(NULL);
   tm=localtime(&t);
   strftime(fecha, 100, "%d/%m/%Y", tm);
   time_t current_time;
   struct tm * time_info;

   time(&current_time);
   time_info = localtime(&current_time);
   strftime(hora, sizeof(hora), "%H:%M:%S", time_info);

    strcpy(fechayhora,fecha);
    strcat(fechayhora," ");
    strcat(fechayhora,hora);


    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    int qstate;
    conn = mysql_init(0);
    if(conn){
        //cout<<"Conexion exitosa"<<endl;
    }
    else{
        cout<<"Eroor de conexion. "<<mysql_error(conn);
    }

    conn = mysql_real_connect(conn,"localhost","root","","tienda",0,NULL,0);

    if(conn)
    {
        system("color a");
        //cout<<"La base de datos esta conectada \n"<<endl;
        string fecha_p = fechayhora;
        string nombre_p,precio_p,fabricante_p;
        fflush(stdin);
        cout<<"Nombre del producto: "; cin>>nombre_p;
        fflush(stdin);
        cout<<"\nPrecio del producto: "; cin>>precio_p;
        fflush(stdin);
        cout<<"\nFabricante del producto: "; cin>>fabricante_p;

        string query="insert into producto(codigo_producto,nombre_producto,precio_producto,fecha_producto,fabricador_producto) values('""','"+nombre_p+"','"+precio_p+"','"+fecha_p+"','"+fabricante_p+"')";

        const char* q = query.c_str();

        cout<<"query is: "<<q<<endl;
        qstate = mysql_query(conn,q);

        if(!qstate)
            cout<<"Consulta procesada satisfactiamente"<<endl;
        else
            cout<<"Hubo problemas en la consulta: "<<mysql_error(conn)<<endl;

        qstate = mysql_query(conn,"SELECT * FROM producto");

        if(!qstate)
        {
            system("color b");
            res = mysql_store_result(conn);
            cout<<"\n\n\n********** BASE DE DATOS **********"<<endl;
            while(row=mysql_fetch_row(res))
            {
                cout<<"Codigo: "<<row[0]<<endl;
                cout<<"Nombre del producto: "<<row[1]<<endl;
                cout<<"Precio del producto: "<<row[2]<<endl;
                cout<<"Fecha de venta: "<<row[3]<<endl;
                cout<<"Fabricante: "<<row[4]<<endl;
            }
        }
        else
        {
            cout<<"Hubo problemas en la consulta: "<<mysql_error(conn)<<endl;
        }
    }else{
        cout<<"Ocurrio un problema en la conexion. "<<mysql_error(conn)<<endl;
    }

    mysql_close(conn);

    return 0;
}
