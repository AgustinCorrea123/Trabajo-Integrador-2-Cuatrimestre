#include <stdio.h>
#include <stdlib.h>
#include "conio.c"
#include <string.h>
#include <ctype.h>

// ESTRUCTURAS
struct fecha
{
    int dia;
    int mes;
    int anio;
};

struct Dia
{
    char dias[6];
};

struct usuario
{
    char apeNom[60];
    char usuario[10];
    char contrasenia[10];
    char tipoUsuario;
    int dni;
};

struct Entrenador
{
    char apeNom[60];
    int legajoEntrenador;
    Dia diaAtencion[6];
    char contrasenia[10];
};

struct Socios
{
    char apeNom[60];
    char domicilio[60];
    int dni;
    int edad;
    fecha fechaDeIngreso;
    char indicacionMedica[100];
    float altura;
    float peso;
    int nroSocio;
};

struct atenciones
{
    char apeNom[60];
    int cantAten;
    float porc;
};

struct actividad
{
    int key;
    char nomActividad[20];
    int hora;
    int legEntrador;
    int cantSocios;
    int nroSocios[50];
    char detalles[380];
};

// FUNCIONES
void menu(bool &b);
bool login();
void listaSociosConActiviades();
void registroRutina();
void listaRutina();

// VARIABLES GLOBALES

Entrenador admin;

int main()
{
    bool band = false, b = true;
    system("mode 120,35");
    do
    {
        system("cls");
        if (login() == true)
            ;
        {
            band = true;
        }
    } while (band == false);
    while (b)
    {
        menu(b);
    }
    return 0;
}

bool login()
{
    FILE *arch = fopen("Entrenador.dat", "r+b");
    Entrenador user;
    bool band = false;

    if (arch == NULL)
    {
        printf("\n\n\t\t No se ha registrado ningun usuario. Por favor solicite uno para poder continuar.");
        system("pause>nul");
        system("exit");
    }
    else
    {
        do
        {
            system("cls");
        	textcolor(RED);
        	printf("\n\n\n\n\t\t\t\t--------|INGRESO ENTRENADOR|--------\n\n");
        	textcolor(WHITE);
            fflush(stdin);
            printf("\n\t\t\tLEGAJO: ");
            scanf("%d", &user.legajoEntrenador);
            printf("\n\t\t\tCONTRASE%cA: ", 165);
            fflush(stdin);
            gets(user.contrasenia);
            rewind(arch);
            fread(&admin, sizeof(Entrenador), 1, arch);
            while (!feof(arch))
            {
                if (user.legajoEntrenador == admin.legajoEntrenador)
                {
                    band = true;
                    break;
                }
                fread(&admin, sizeof(Entrenador), 1, arch);
            }
            if (band == true)
            {
                if (strcmp(user.contrasenia, admin.contrasenia) == 0)
                {
                    band = true;
                    system("cls");
                    return true;
                }
                else
                {
                    printf("\n\t\t%cNOTA: ", 175);
                    textcolor(YELLOW);
                    printf("\n\n\t\t\tLa contrase%ca no coincide con el usuario. ", 164);
                    textcolor(WHITE);
                    system("pause>nul");
                    system("cls");
                    band = false;
                }
            }
            else
            {
                printf("\n\t\t\tNOTA:");
                textcolor(YELLOW);
                printf("\n\n\t\t\tEl usuario no existe. ");
                textcolor(WHITE);
                system("pause>nul");
                system("cls");
            }
        } while (band == false);
        fclose(arch);
        return true;
    }
}

void menu(bool &b)
{
    bool band = true;
    int Op;
    const char *titulo = "Modulo de Gym";
    const char *opciones[] = {"Listado de Socios y actividad que desarrolla", "Registro de Rutina", "Lista de Rutinas", "Salir"};
    do
    {
        system("cls");
        textcolor(RED);
        printf("\n\n\n\n\t\t\t\t--------|%s|--------\n\n\n", titulo);
        textcolor(WHITE);
        for (int i = 0; i < 4; i++)
        {
            printf("\t\t\t  %d. %s\n", i + 1, opciones[i]);
        }
        printf("\n\t\t\tIngrese una opcion: ");
        scanf("%d", &Op);
        switch (Op)
        {
        case 1:
            system("cls");
            listaSociosConActiviades();
            break;
        case 2:
            system("cls");
            registroRutina();
            break;
        case 3:
            system("cls");
            listaRutina();
            break;
        case 4:
            band = false, b = false;
            break;
        default:
            system("cls");
            printf("\n\n\t\tError, respuesta invalida\n\n");
        }
    } while (band);
    system("cls");
    printf("\n\n\n\n\t\t\t\tSe cerro el modulo de Gym. Adios...\n\n\n\n");
    system("pause>nul");
}

void listaSociosConActiviades()
{

    FILE *arch = fopen("Socios.dat", "r+b");
    FILE *arch1 = fopen("Actividades.dat", "r+b");
    FILE *arch2 = fopen("Entrenador.dat", "r+b");

    Socios soc;
    actividad act;
    Entrenador ent;

    int cont = 0, cont2 = 0;
    
    system("cls");
    textcolor(RED);
    printf("\n\n\t\t\t\t------|LISTADO DE SOCIOS|------\n\n");
    textcolor(WHITE);
    rewind(arch);
    fread(&soc, sizeof(Socios), 1, arch);
    while (!feof(arch))
    {
        if (cont == 5)
        {
            printf("\n\n\t\tPRESIONE ENTER PARA CONTINUAR VIENDO SOCIOS...");
            system("pause>nul");
            system("CLS");
            cont = 0;
            printf("\n\n\t\t\t\t---- | Listado de Socios y Actividades que desarrolla | ----\n\n");
        }
        printf("\n\t\tNUMERO DE SOCIO: %d", soc.nroSocio);
        printf("\n\t\tAPELLIDO Y NOMBRE: %s", soc.apeNom);
        printf("\n\t\tACTIVIDAD QUE DESARROLLA: ");
        rewind(arch1);
        fread(&act, sizeof(actividad), 1, arch1);
        while (!feof(arch1))
        {
            if (cont2 == 2)
            {
                printf("\n");
            }

            for (int i = 0; i < 50; i++)
            {
                if (act.nroSocios[i] == soc.nroSocio and admin.legajoEntrenador == act.legEntrador)
                {
                    rewind(arch2);
                    fread(&ent, sizeof(Entrenador), 1, arch2);
                    while (!feof(arch2))
                    {
                        if (act.legEntrador == ent.legajoEntrenador)
                        {
                            break;
                        }
                        fread(&ent, sizeof(Entrenador), 1, arch2);
                    }
                    cont2++;
                    printf("\n\t\t%s con %s a las %d HS. \n", act.nomActividad, ent.apeNom, act.hora);
                    break;
                }
            }

            fread(&act, sizeof(actividad), 1, arch1);
        }
        printf("\n\n-----------------------------------------------------------------------------------------------\n");
        fread(&soc, sizeof(Socios), 1, arch);
        cont++;
    }
    system("pause>nul");
    fclose(arch);
    fclose(arch1);
    fclose(arch2);
}

void registroRutina()
{

    FILE *arch = fopen("Actividades.dat", "r+b");

    Entrenador ent;
    actividad act;
    Socios soc;

    int cont = 0, op;
    int arrAct[cont + 1];
    
    system("cls");
    textcolor(RED);
    printf("\n\n\t\t\t\t------|REGISTRO RUTINA|------\n\n");
    textcolor(WHITE);
    
    rewind(arch);
    fread(&act, sizeof(actividad), 1, arch);
    while (!feof(arch))
    {
        if (act.legEntrador == admin.legajoEntrenador)
        {

            printf("\n\t\t\t%d- %s a la hora %d \n", cont + 1, act.nomActividad, act.hora);
            arrAct[cont] = act.key;
            cont++;
        }
        fread(&act, sizeof(actividad), 1, arch);
    }
    printf("\n\n\t\tIngrese la opcion: ");
    scanf("%d", &op);
    rewind(arch);
    fread(&act, sizeof(actividad), 1, arch);
    while (!feof(arch))
    {
        if (act.key == arrAct[op - 1])
        {
            printf("\n\n\t\tINGRESA DETALLE DE DICHA ACTIVIDAD SELECCIONADA: \n\n\t\t\t\t");
            _flushall();
            gets(act.detalles);
            break;
        }
        fread(&act, sizeof(actividad), 1, arch);
    }

    fseek(arch, (act.key - 1) * sizeof(actividad), SEEK_SET);
    fwrite(&act, sizeof(actividad), 1, arch);
    fclose(arch);
}

void listaRutina()
{

    FILE *arch = fopen("Actividades.dat", "r+b");

    actividad act;
    system("cls");
    textcolor(RED);
    printf("n\n\t\t\t\t---- | Lista de Actividades con Detalles de Rutinas | ----\n\n");
    textcolor(WHITE);
    rewind(arch);
    fread(&act, sizeof(actividad), 1, arch);
    while (!feof(arch))
    {
        if (admin.legajoEntrenador == act.legEntrador)
        {
            printf("\n\t\t\tLa activiadad %s a la hora %d", act.nomActividad, act.hora);
            printf("\n\t\t\tDetalle: %s", act.detalles);
            printf("\n\n\t-----------------------------------------------------------------------------------------------\n");
        }
        fread(&act, sizeof(actividad), 1, arch);
    }
    system("pause>nul");
    fclose(arch);
}
