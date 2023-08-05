/*	HONORARIOS
	Autor: Marco Antonio Puga Malagòn */

//LIBRERIAS
#include <stdio.h>
#include <conio.h>
#include <string.h>

//ESTRUCTURA PARA FICHEROS
typedef struct recibos
{
	//Campos
	char nr[6];
	char fecha[20];
	char rfc[30];
	//HONORARIOS
	float hns;
	float pagoiva;
	float subtotal;
	float retiva;
	float retisr;
	float total;
} Recibo;
typedef struct reportes
{
   //Reporte
   char r1[6]; //Numero de recibo
   char r2[21]; //Fecha
   char r3[31]; //RFC
   char r4[10]; //Honorarios
   char r5[10]; //IVA
   char r6[10]; //Subtotal
   char r7[10]; //Ret IVA
   char r8[10]; //Ret ISR
   char r9[10]; //Total
} Reporte;

//FUNCIONES DE INTERFAS
void interfas(void);
void start(void);
void menu(void);
void txtdatos(void);
void sel_op(char opcion);
void sel_opn(char opcion);
void sel_opr(char opcion);

//Funciones PARA MANEJO FICHEROS
void cargar(), guardar(), guardarrep(), insertar(Recibo info), insertarr(Reporte info);
void ingresar(), consultar(), listar(), modificar(), eliminar(), ordenar(), crp();

//AREGLOS
char textnr[10][25]={"\r  Recibo: #\n\n",
							"\r  Fecha:       \n\n",
                  	"\r  R.F.C:       \n\n",
                  	"\r  Honorarios:     $\n\n",
                  	"\r  Pago de IVA:    $\n\n",
                  	"\r  Subtotal:       $\n\n",
                  	"\r  Ret 10.67%% IVA: $\n\n",
                  	"\r  Ret 10%%  ISR:   $\n\n",
                  	"\r  TOTAL:          $" };
//Almacena recibos
Recibo recibos[100];
Reporte reportes[100];

//VARIABLES GLOBALES
char op;
int qpex;
int i;
//Numero de recibos alcual
int totalr = 0;
int trr = 0;

//////////////////////////////////MAIN/////////////////////////////////////////
main()
{
   //FICHEROS
   cargar();
   //INTERFAS
	do { interfas(); menu(); start(); }while(qpex==1);
}
///////////////////////////////////////////////////////////////////////////////
void interfas(void)
{
	clrscr();
	textbackground(0); clrscr();
   window(1,1,80,29); textbackground(3); clrscr();
   gotoxy(33,1); textcolor(0); cprintf("HONORARIOS");
   window(2,2,79,28); textbackground(1); clrscr();
}
void start(void)
{
	gotoxy(1,1); textcolor(4); cscanf("%c",&op); sel_op(op);
}
void menu(void)
{
	window(2,2,79,2); textbackground(4); clrscr();
	gotoxy(2,1); textcolor(15); cprintf("|Nuevo|  |Registro|  |Ayuda|  |Salir|");
}
void txtdatos(void)
{
   int a;
	for(a=0; a<=9; a++)
   {
   	textcolor(15); cprintf(textnr[a]);
   }
}
void sel_op(char opcion)
{
	switch(opcion)
   {
   	case 'N':
   	case 'n':
			window(4,4,15,12); textbackground(0); clrscr();
			window(3,3,14,11); textbackground(4); clrscr();
         gotoxy(2,2); textcolor(15); cprintf("1 Recibo");
         gotoxy(2,4); textcolor(15); cprintf("2 Consulta");
         gotoxy(2,6); textcolor(15); cprintf("3 Lista");
         gotoxy(2,8); textcolor(15); cprintf("4 Reporte");
         textcolor(4); cscanf("%c",&op); sel_opn(op);
         qpex=1;
	   	break;
    case 'R':
   	case 'r':
			window(13,4,25,10); textbackground(0); clrscr();
			window(12,3,24,9); textbackground(4); clrscr();
         gotoxy(2,2); textcolor(15); cprintf("1 Modificar");
         gotoxy(2,4); textcolor(15); cprintf("2 Eliminar");
         gotoxy(2,6); textcolor(15); cprintf("3 Ordenar");
         textcolor(4); cscanf("%c",&op); sel_opr(op);
      	qpex=1;
	   	break;
    case 'A':
   	case 'a':
			window(25,4,40,6); textbackground(0); clrscr();
			window(24,3,39,5); textbackground(4); clrscr();
         gotoxy(2,2); textcolor(15); cprintf("1 Acerca de...");
         if(getche()=='1')
         {
            interfas();
            menu();
         	window(21,6,57,11); textbackground(0); clrscr();
         	window(20,5,56,10); textbackground(4); clrscr();
            textcolor(15); gotoxy(2,2); cprintf("Honorarios 2010");
            textcolor(15); gotoxy(2,3); cprintf("Ver: 1.5");
            textcolor(15); gotoxy(2,5); cprintf("Autor:");
				textcolor(15); gotoxy(2,8); cprintf(" PUGA MALAGON MARCO ANTONIO");
         }
      	qpex=1;
	   	getch();
	   	break;
      case 'S':
      case 's':
			qpex=0;
         break;
   	default:
   		qpex=1;
   }
}
void sel_opn(char opcion)
{
	switch(opcion)
   {
      case '1':
         interfas();
         menu();
      	window(30,4,58,5); textbackground(3); clrscr();
         textcolor(15); gotoxy(2,1); cprintf("NUEVO RECIBO");
			window(31,6,59,27); textbackground(0); clrscr();
         window(30,5,58,26); textbackground(4); clrscr();
         gotoxy(2,2); txtdatos();
         ingresar();
         break;
      case '2':
      	interfas();
         menu();
         window(30,4,55,4); textbackground(3); clrscr();
         textcolor(15); gotoxy(2,1); cprintf("CONSULTAR RECIBO");
         window(31,6,56,8); textbackground(0); clrscr();
         window(30,5,55,7); textbackground(4); clrscr();
         gotoxy(2,2); textcolor(15); cprintf("Consultar recibo: #");
         consultar();
         getch();
         break;
      case '3':
      	interfas();
         menu();
         window(5,4,75,4); textbackground(3); clrscr();
         textcolor(15); gotoxy(30,1); cprintf("LISTA DE RECIBOS");
         window(6,6,76,21); textbackground(0); clrscr();
         window(5,5,75,20); textbackground(4); clrscr();
         textcolor(15); gotoxy(2,2); cprintf("Presione (L) para listar... ");
         switch(getche())
         {
         	case 'l':
            case 'L':
            	listar();
         }
         getch();
         break;
      case '4':
			interfas();
         menu();
         window(5,4,75,4); textbackground(3); clrscr();
         textcolor(15); gotoxy(30,1); cprintf("REPORTE DE RECIBOS");
         window(6,6,76,21); textbackground(0); clrscr();
         window(5,5,75,20); textbackground(4); clrscr();
         textcolor(15); gotoxy(2,2); cprintf("Presione (R) para generar el reporte... ");
         switch(getche())
         {
         	case 'r':
            case 'R':
            	crp();
         }
         getch();
         break;
   }
}
void sel_opr(char opcion)
{
	switch(opcion)
   {
      case '1':
      	interfas();
         menu();
         window(30,4,55,4); textbackground(3); clrscr();
         textcolor(15); gotoxy(2,1); cprintf("MODIFICAR RECIBO");
         window(31,6,56,8); textbackground(0); clrscr();
         window(30,5,55,7); textbackground(4); clrscr();
         gotoxy(2,2); textcolor(15); cprintf("Modificar recibo: #");
         modificar();
         getch();
         break;
      case '2':
      	interfas();
         menu();
         window(30,4,55,4); textbackground(3); clrscr();
         textcolor(15); gotoxy(2,1); cprintf("ELIMINAR RECIBO");
         window(31,6,56,8); textbackground(0); clrscr();
         window(30,5,55,7); textbackground(4); clrscr();
         gotoxy(2,2); textcolor(15); cprintf("Eliminar recibo: #");
         eliminar();
         getch();
         break;
      case '3':
      	interfas();
         menu();
         window(15,4,57,4); textbackground(3); clrscr();
         textcolor(15); gotoxy(2,1); cprintf("ORDENAR RECIBOS");
         window(16,6,58,10); textbackground(0); clrscr();
         window(15,5,57,9); textbackground(4); clrscr();
         gotoxy(2,2); textcolor(15); cprintf("Presione (O) para ordenar los recibos: ");
         switch(getche())
         {
         	case 'O':
            case 'o':
            	ordenar();
         }
         getch();
         break;
   }
}
///////////////////// AREA DE FUNCIONES DE FICHEROS /////////////////////
void cargar() //Carga fichero
{
	Recibo info;
	FILE *fp;

	fp=fopen("honosbd.pug","r");
	if(fp==NULL)
	{
		textcolor(15); cprintf("NO SE PUEDE ABRIR <honosbd.pug>");
		return;
	}
	while(!feof(fp))
	{
		if(fread(&info, sizeof(Recibo), 1, fp)!=1) break;
		insertar(info);
	}
	fclose(fp);
}
void ingresar()
{
	Recibo info;

   	fflush(stdin);
  	gotoxy(12,2); gets(info.nr);
	gotoxy(10,4); gets(info.fecha);
	gotoxy(10,6); gets(info.rfc);
	gotoxy(20,8); scanf("%f",&info.hns);

		info.pagoiva = ((info.hns)*(.16));
	gotoxy(20,10); textcolor(15); cprintf("%.2f",info.pagoiva);

	info.subtotal = ((info.hns)*(1.16));
	gotoxy(20,12); textcolor(15); cprintf("%.2f",info.subtotal);

	info.retiva = ((info.hns)*(.1067));
	gotoxy(20,14); textcolor(15); cprintf("%.2f",info.retiva);

	info.retisr = ((info.hns)*(.10));
	gotoxy(20,16); textcolor(15); cprintf("%.2f",info.retisr);

	info.total = ((info.subtotal)-((info.retiva)+(info.retisr)));
	gotoxy(20,18); textcolor(15); cprintf("%.2f",info.total);

	insertar(info);
	gotoxy(3,20); textcolor(15); cprintf("Recibo ingresado con exito");
   	gotoxy(3,21); textcolor(15); cprintf("Para guardar presione (G)");
   switch(getche())
   {
   	case 'g':
      case 'G':
      	guardar();
         break;
      default:
      	totalr=totalr-1;
      	break;
   }
}
void insertar(Recibo info)
{
	strcpy(recibos[totalr].nr, info.nr);
	strcpy(recibos[totalr].fecha, info.fecha);
	strcpy(recibos[totalr].rfc, info.rfc);
	recibos[totalr].hns = info.hns;
	recibos[totalr].pagoiva = info.pagoiva;
	recibos[totalr].subtotal = info.subtotal;
	recibos[totalr].retiva = info.retiva;
	recibos[totalr].retisr = info.retisr;
	recibos[totalr].total = info.total;
	totalr++;
}
void guardar()
{
	Recibo info;
	FILE *fp;
	fp=fopen("honosbd.pug","w");
	if(fp==NULL)
	{
		gotoxy(3,21); textcolor(15); cprintf("NO SE PUEDE GUARDAR EN <honosbd.pug>");
		return;
	}
	for(int i=0; i<totalr; i++)
		fwrite(&recibos[i], sizeof(Recibo), 1, fp);
	fclose(fp);
}
void consultar()
{
	char nrecibo[6];

	gotoxy(21,2); gets(nrecibo);
	txtdatos();
	for(i=0; i<totalr; i++)
		if(!strcmp(recibos[i].nr, nrecibo))
		{
         interfas();
         menu();
      	window(30,4,58,5); textbackground(3); clrscr();
         textcolor(15); gotoxy(2,1); cprintf("DATOS DEL RECIBO");
			window(31,6,59,24); textbackground(0); clrscr();
         window(30,5,58,23); textbackground(4); clrscr();
         gotoxy(2,2); txtdatos();
			gotoxy(12,2); cprintf("%s", recibos[i].nr);
			gotoxy(10,4); cprintf("%s", recibos[i].fecha);
			gotoxy(10,6); cprintf("%s", recibos[i].rfc);
			gotoxy(18,8); cprintf("%.2f", recibos[i].hns);
			gotoxy(18,10);	cprintf("%.2f",recibos[i].pagoiva);
			gotoxy(18,12); cprintf("%.2f", recibos[i].subtotal);
			gotoxy(18,14); cprintf("%.2f", recibos[i].retiva);
			gotoxy(18,16);	cprintf("%.2f", recibos[i].retisr);
			gotoxy(18,18);	cprintf("%.2f", recibos[i].total);
			break;
		}
  	if(i==totalr)
   {
      interfas();
      menu();
      window(30,4,55,4); textbackground(3); clrscr();
      textcolor(15); gotoxy(2,1); cprintf("CONSULTAR RECIBO");
      window(31,6,56,8); textbackground(0); clrscr();
   	window(30,5,55,7); textbackground(4); clrscr();
      gotoxy(2,2); textcolor(15); cprintf("El recibo no existe."); }
}
void listar()
{
	interfas();
   menu();
   window(5,4,75,4); textbackground(3); clrscr();
   textcolor(15); gotoxy(30,1); cprintf("LISTA DE RECIBOS");
   window(6,6,76,21); textbackground(0); clrscr();
   window(5,5,75,20); textbackground(4); clrscr();
   textcolor(15);
   cprintf("\n |#| - | FECHA | - |   R.F.C  | - |  HONORARIOS  | - | TOTAL  |\n");
   cprintf("\r --------------------------------------------------------------\n");
   for(int i=0; i<totalr; i++)
   {
		cprintf("\r |%s| - ", recibos[i].nr);
		cprintf("|%s| - ", recibos[i].fecha);
  		cprintf("|%s| - ", recibos[i].rfc);
		cprintf("|$%.2f     | - ", recibos[i].hns);
		cprintf("|$%.2f|\n", recibos[i].total);
   }
}
void modificar()
{
	char nrecibo[6];

	gotoxy(21,2); gets(nrecibo);

	for(i=0; i<totalr; i++)
		if(!strcmp(recibos[i].nr, nrecibo))
		{
         interfas();
         menu();
      	window(30,4,58,5); textbackground(3); clrscr();
         textcolor(15); gotoxy(2,1); cprintf("MODIFICAR RECIBO");
			window(31,6,59,24); textbackground(0); clrscr();
         window(30,5,58,23); textbackground(4); clrscr();
         gotoxy(2,2); txtdatos();
         fflush(stdin);
   		gotoxy(12,2); gets(recibos[i].nr);
			gotoxy(10,4); gets(recibos[i].fecha);
			gotoxy(10,6); gets(recibos[i].rfc);
			gotoxy(18,8); scanf("%f",&recibos[i].hns);

  			recibos[i].pagoiva = ((recibos[i].hns)*(.16));
			gotoxy(18,10); textcolor(15); cprintf("%.2f",recibos[i].pagoiva);

			recibos[i].subtotal = ((recibos[i].hns)*(1.16));
			gotoxy(18,12); textcolor(15); cprintf("%.2f",recibos[i].subtotal);

			recibos[i].retiva = ((recibos[i].hns)*(.1067));
			gotoxy(18,14); textcolor(15); cprintf("%.2f",recibos[i].retiva);

			recibos[i].retisr = ((recibos[i].hns)*(.10));
			gotoxy(18,16); textcolor(15); cprintf("%.2f",recibos[i].retisr);

			recibos[i].total = ((recibos[i].subtotal)-((recibos[i].retiva)+(recibos[i].retisr)));
			gotoxy(18,18); textcolor(15); cprintf("%.2f",recibos[i].total);

			guardar();
			gotoxy(2,19); textcolor(15); cprintf("Recibo modificado con exito");
  	break;
		}
  	if(i==totalr)
   {
      interfas();
      menu();
      window(30,4,55,4); textbackground(3); clrscr();
      textcolor(15); gotoxy(2,1); cprintf("MODIFICAR RECIBO");
      window(31,6,56,8); textbackground(0); clrscr();
   	window(30,5,55,7); textbackground(4); clrscr();
      gotoxy(2,2); textcolor(15); cprintf("El recibo no existe."); }
}
void eliminar()
{
	char nrecibo[6];

	gotoxy(21,2); gets(nrecibo);
   textcolor(15);
   for(i=0; i<totalr; i++)
      if(!strcmp(recibos[i].nr, nrecibo))
      {
         /* Recorre registros posteriores */
         for(int j=i+1; j<totalr; j++)
         {
            strcpy(recibos[j-1].nr, recibos[j].nr);
            strcpy(recibos[j-1].fecha, recibos[j].fecha);
	         strcpy(recibos[j-1].rfc, recibos[j].rfc);
            recibos[j-1].hns = recibos[j].hns;
            recibos[j-1].pagoiva = recibos[j].pagoiva;
            recibos[j-1].subtotal = recibos[j].subtotal;
            recibos[j-1].retiva = recibos[j].retiva;
            recibos[j-1].retisr = recibos[j].retisr;
            recibos[j-1].total = recibos[j].total;
         }

         gotoxy(2,2); cprintf("Recibo eliminado.");
         totalr--;
         guardar();
         break;
      }

   if(i==totalr){ gotoxy(2,2); cprintf("El recibo no existe."); }
}
void ordenar()
{
	int j;
   Recibo temp;

   for(i=0; i<totalr-1; i++)
   {
      for(j=i+1; j<totalr; j++)
      if(strcmp(recibos[i].nr, recibos[j].nr)>0)
      {
         /* Copia en variable temporal datos actuales */
         strcpy(temp.nr, recibos[i].nr);
         strcpy(temp.fecha, recibos[i].fecha);
         strcpy(temp.rfc, recibos[i].rfc);
         temp.hns = recibos[i].hns;
         temp.pagoiva = recibos[i].pagoiva;
         temp.subtotal = recibos[i].subtotal;
         temp.retiva = recibos[i].retiva;
         temp.retisr = recibos[i].retisr;
         temp.total = recibos[i].total;

         /* Intercambia informacion */
         strcpy(recibos[i].nr, recibos[j].nr);
         strcpy(recibos[i].fecha, recibos[j].fecha);
         strcpy(recibos[i].rfc, recibos[j].rfc);
         recibos[i].hns = recibos[j].hns;
      	recibos[i].pagoiva = recibos[j].pagoiva;
         recibos[i].subtotal = recibos[j].subtotal;
         recibos[i].retiva = recibos[j].retiva;
         recibos[i].retisr = recibos[j].retisr;
         recibos[i].total = recibos[j].total;

         strcpy(recibos[j].nr, temp.nr);
         strcpy(recibos[j].fecha, temp.fecha);
         strcpy(recibos[j].rfc, temp.rfc);
         recibos[j].hns = temp.hns;
         recibos[j].pagoiva = temp.pagoiva;
         recibos[j].subtotal = temp.subtotal;
         recibos[j].retiva = temp.retiva;
         recibos[j].retisr = temp.retisr;
         recibos[j].total = temp.total;
      }
   }
   guardar();
   gotoxy(2,4); textcolor(15); cprintf("Se han ordenado los recibos.");
}
void crp()
{
   fflush(stdin);
   Reporte info;
   char a[10];
   for(int i=0; i<totalr; i++)
   {
   	strcpy(info.r1, recibos[i].nr);
		strcpy(info.r2, recibos[i].fecha);
		strcpy(info.r3, recibos[i].rfc);
		sprintf(a, " $%.2f", recibos[i].hns);
      strcpy(info.r4, a);
  		sprintf(a, " $%.2f", recibos[i].pagoiva);
      strcpy(info.r5, a);
  		sprintf(a, " $%.2f", recibos[i].subtotal);
      strcpy(info.r6, a);
  		sprintf(a, " $%.2f", recibos[i].retiva);
      strcpy(info.r7, a);
  		sprintf(a, " $%.2f", recibos[i].retisr);
      strcpy(info.r8, a);
  		sprintf(a, " $%.2f\n", recibos[i].total);
      strcpy(info.r9, a);
      insertarr(info);
   }
   guardarrep();
}
void insertarr(Reporte info)
{
	strcpy(reportes[trr].r1, info.r1);
	strcpy(reportes[trr].r2, info.r2);
	strcpy(reportes[trr].r3, info.r3);
 	strcpy(reportes[trr].r4, info.r4);
 	strcpy(reportes[trr].r5, info.r5);
	strcpy(reportes[trr].r6, info.r6);
 	strcpy(reportes[trr].r7, info.r7);
 	strcpy(reportes[trr].r8, info.r8);
 	strcpy(reportes[trr].r9, info.r9);
	trr++;
}
void guardarrep()
{
	Reporte info;
	FILE *fp;
	fp=fopen("Reporte.txt","w");
	if(fp==NULL)
	{
		gotoxy(3,21); textcolor(15); cprintf("NO SE PUEDE CREAR REPORTE");
		return;
	}
	for(int i=0; i<totalr; i++)
		fwrite(&reportes[i], sizeof(Reporte), 1, fp);
	fclose(fp);
}
