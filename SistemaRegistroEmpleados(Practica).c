#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#define p printf
#define s scanf

typedef struct
{
	char nombreApellido[35];
	int codEmpleado;
	int edad;
	float salario;
}empleados;

int menu(void);
void agregarEmpleado(FILE *, int *);
void mostrarEmpleados(FILE *);
empleados buscarEmpleado(FILE *);
void eliminarEmpleado(FILE *);
void modificarDatos(FILE *);
FILE* inicio(FILE *, char *);
void salida(void);
void linea(int cant);

int main()
{
	system("Color 04");
	int op,codE = 1;//Código empleado.
	FILE *archivo;
	char *nomArchivo="empleados.dat";
	int *q;
	empleados registro;
	
	
	q = &codE;
	
	if((archivo=inicio(archivo,nomArchivo))==NULL)
		return 0;
	
	do
	{
		op = menu();
		switch(op)
		{
			case 1:
				agregarEmpleado(archivo,q);
				op=10;
				break;
			case 2:
				mostrarEmpleados(archivo);
				op=10;
				break;
			case 3:
				registro = buscarEmpleado(archivo);
				op=10;
				break;
			case 4:
				eliminarEmpleado(archivo);
				op=10;
				break;
			case 5:	
				modificarDatos(archivo);
				op=10;			
				break;	
			case 6:
				salida();
				fclose(archivo);
				break;
		}		
	}while(op<1 || op>6);
	
	
	
	return 0;
}

int menu()
{
	int op;
	
	do
	{
		system("cls");
		p("\t\t--SISTEMA DE GESTION DE EMPLEADOS--\n");
		p("\t\t\t[1]-Agregar empleado\n");
		p("\t\t\t[2]-Mostrar empleados\n");
		p("\t\t\t[3]-Buscar empleado\n");
		p("\t\t\t[4]-Eliminar empleado\n");
		p("\t\t\t[5]-Modificar datos empleado\n");
		p("\t\t\t[6]-Salir\n");
		s("%d",&op);
	}while(op<1 || op>6);
		
	return op;
}

void agregarEmpleado(FILE *archivo, int *codE)
{
	system("cls");
	rewind(archivo);
	empleados registro;
	int i = 1;
	
	p("\t\t--REGISTRO DE EMPLEADO--\n");
	fseek(archivo,0l,SEEK_END);
	do
	{
		p("--Cuando desee terminar el registro ingrese un '0' (cero)--\n");
		p("Ingrese el nombre y el apellido: ");
		fflush(stdin);
		gets(registro.nombreApellido);
		registro.codEmpleado = (*codE)++;
		p("Ingrese la edad: ");
		s("%d",&registro.edad);
		p("Ingrese el salario: ");
		s("%f",&registro.salario);
		fwrite(&registro,sizeof(registro),1,archivo);
		p("--Desea registrar otro empleado?--\n");
		s("%d",&i);
	}while(i!=0);
}

void mostrarEmpleados(FILE *archivo)
{
	system("cls");
	rewind(archivo);
	empleados registro;
	
	linea(100);
	p("\t\t--EMPLEADOS--\n");
	
	fread(&registro,sizeof(registro),1,archivo);
	while(!feof(archivo))
	{
		if(registro.codEmpleado != -1)
		{
			p("-NOMBRE Y APELLIDO: %s\n",registro.nombreApellido);
			p("-CODIGO EMPLEADO: %d\n",registro.codEmpleado);
			p("-EDAD: %d\n",registro.edad);
			p("-SALARIO: $%.2f\n",registro.salario);
			p("\n");
		}
		fread(&registro,sizeof(registro),1,archivo);
	}
	linea(100);
	system("Pause");
}

empleados buscarEmpleado(FILE *archivo)
{
	system("cls");
	rewind(archivo);
	empleados registro;
	int codEm;//Código empleado.
	int flag = 0;
	
	p("--Ingrese el codigo del empleado: ");
	s("%d",&codEm);
	
	fread(&registro,sizeof(registro),1,archivo);
	while(!feof(archivo))
	{
		if(codEm == -1)
			flag = 0;
		else if(codEm == registro.codEmpleado)
		{
			linea(100);
			p("\t\t--EMPLEADO %d--\n",codEm);
			p("-NOMBRE Y APELLIDO: %s\n",registro.nombreApellido);
			p("-CODIGO EMPLEADO: %d\n",registro.codEmpleado);
			p("-EDAD: %d\n",registro.edad);
			p("-SALARIO: $%.2f\n",registro.salario);
			linea(100);
			flag++;
			break;
		}
		fread(&registro,sizeof(registro),1,archivo);
	}
	
	if(flag == 0)
	{
		p("\t\t***ERROR: el codigo de empleado ingresado, no corresponde a ningun empleado***\n");	
	}
	
	system("Pause");
	return registro;
}

void eliminarEmpleado(FILE *archivo)
{
	empleados registro = buscarEmpleado(archivo);
	int op,salida;
	
	while(salida != 2)
	{
		do
		{
			p("--Desea eliminar a este empleado?: \n");
			p("[1]-Si\n");
			p("[2]-No\n");
			s("%d",&op);
			
			switch(op)
			{
				case 1:
					registro.codEmpleado = -1;
					fseek(archivo,-sizeof(registro),SEEK_CUR);
					fwrite(&registro,sizeof(registro),1,archivo);
					p("\t\t--EMPLEADO ELIMINADO--\n");
					break;
				case 2:
					salida = 2;
					break;
				
			}	
		}while(op<1 || op>2);
		p("\n--Desea eliminar otro empleado?\n");
		p("[1]-Si\n");
		p("[2]-No\n");
		s("%d",&salida);
		while(salida<1 || salida>2)
		{
			p("\t\t***ERROR: la opcion ingresada no existe***\n");
			p("\n--Desea eliminar otro empleado?\n");
			p("[1]-Si\n");
			p("[2]-No\n");
			s("%d",&salida);
		}
	}
	system("Pause");
}

void modificarDatos(FILE *archivo)
{
	empleados registro = buscarEmpleado(archivo);
	int op,salida;
	
	while(salida!=2)
	{
		do
		{
			p("\n--Que desea modificar?: \n");
			p("[1]-Nombre y apellido\n");
			p("[2]-Codigo empleado\n");
			p("[3]-Edad\n");
			p("[4]-Salario\n");
			s("%d",&op);	
			
			switch(op)
			{
				case 1:
					p("Ingrese el nuevo nombre y el apellido: \n");
					gets(registro.nombreApellido);
					fseek(archivo,-sizeof(registro),SEEK_CUR);
					fwrite(&registro,sizeof(registro),1,archivo);
					break;
				case 2:
					p("Ingrese el nuevo codigo de empleado: \n");
					s("%d",&registro.codEmpleado);
					fseek(archivo,-sizeof(registro),SEEK_CUR);
					fwrite(&registro,sizeof(registro),1,archivo);
					break;
				case 3:
					p("Ingrese la nueva edad: \n");
					s("%d",&registro.edad);
					fseek(archivo,-sizeof(registro),SEEK_CUR);
					fwrite(&registro,sizeof(registro),1,archivo);
					break;
				case 4:
					p("Ingrese el nuevo salario: \n");
					s("%f",&registro.salario);
					fseek(archivo,-sizeof(registro),SEEK_CUR);
					fwrite(&registro,sizeof(registro),1,archivo);
					break;
			}
		}while(op<1 || op>4);
		p("\n--Desea modificar algo mas?\n");
		p("[1]-Si\n");
		p("[2]-No\n");
		s("%d",&salida);
		while(salida<1 || salida>2)
		{
			p("\t\t***ERROR: la opcion ingresada no existe***\n");
			p("\n--Desea modificar algo mas?\n");
			p("[1]-Si\n");
			p("[2]-No\n");
			s("%d",&salida);
		}
	}
	
	p("\t\t--CAMBIOS GUARDADOS--\n");
	system("Pause");
}

FILE* inicio(FILE *archivo, char *nomArchivo)
{
	int op;
		
	if((archivo=fopen(nomArchivo,"rb+"))==NULL)
	{
		p("\t\t***ERROR: el archivo [%s] no existe***\n",nomArchivo);
		p("Desea crearlo?\n");
		p("[1]-Si\n");
		p("[2]-No\n");
		s("%d",&op);
		
		if(op == 1)
		{
			if((archivo=fopen(nomArchivo,"wb+"))==NULL)
				p("\t\t***ERROR: no se pudo crear el archivo [%s]***\n",nomArchivo);
			else
				p("--Archivo [%s] creado con exito--\n",nomArchivo);
			system("Pause");
		}
		else if(op == 2)
		{
			salida();
		}
		else
		{	
			while(op<1 || op>2)
			{
				p("\t\t***ERROR: la opcion ingresada no existe***\n");
				p("Desea crearlo?\n");
				p("[1]-Si\n");
				p("[2]-No\n");
				s("%d",&op);
			}
			if(op == 2)
			{
				salida();
			}
				
		}
	}	
	else
	{
		p("--Archivo [%s] abierto con exito--\n",nomArchivo);
		system("Pause");
	}
	
	return archivo;	
}

void salida()
{
	system("cls");
	p("\t\t***Cerrando el programa***");
	getch();
}

void linea(int cant)
{
	int i;
	p("\n");
	for(i=0;i<cant;i++)
	{
		p("-");
	}
	p("\n");
}
