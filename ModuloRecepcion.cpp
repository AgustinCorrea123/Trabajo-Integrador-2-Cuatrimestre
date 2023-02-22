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

usuario admin;

// FUNCIONES
bool login();
void menu(bool &b);
void registroSocio();
void regActividadesSocio();
void listaSocios();
int arrLibre(actividad act);
void listaPagoSocios();

int main()
{
    bool band = false, b = true;
    do
    {
        system("cls");
        if (login() == true)
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
    FILE *arch = fopen("Usuarios.dat", "r+b");
    usuario user;
    bool band = false;

    if (arch == NULL)
    {
        printf("\n\n\n\n\t\t No se ha registrado ningun RECEPCIONISTA. Por favor registre uno.");
        system("pause>nul");
        system("exit");
    }
    else
    {
        do
        {
            system("cls");
        	textcolor(RED);
        	printf("\n\n\n\n\t\t\t\t--------|INGRESO RECEPCION|--------\n\n");
        	textcolor(WHITE);
            fflush(stdin);
            printf("\n\t\t\tUSUARIO: ");
            gets(user.usuario);
            printf("\n\t\t\tCONTRASE%cA: ", 165);
            gets(user.contrasenia);
            rewind(arch);
            fread(&admin, sizeof(usuario), 1, arch);
            while (!feof(arch))
            {
                if (strcmp(user.usuario, admin.usuario) == 0)
                {
                    band = true;
                    break;
                }
                fread(&admin, sizeof(usuario), 1, arch);
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
                    printf(" %cNOTA: ", 175);
                    textcolor(YELLOW);
                    printf(" La contrase%ca no coincide con el usuario. ", 164);
                    textcolor(WHITE);
                    system("pause>nul");
                    system("cls");
                    band = false;
                }
            }
            else
            {
                printf("NOTA:");
                textcolor(YELLOW);
                printf(" El usuario no existe. ");
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
    const char *titulo = "Modulo de Recepcion";
    const char *opciones[] = {"Registrar Socio", "Registrar Actividades de Socio", "Listado de Socios", "Listado de fechas de pagos", "Salir"};
    do
    {
        system("cls");
        textcolor(RED);
        printf("\n\n\n\n\t\t\t\t--------|%s|--------\n\n\n", titulo);
        textcolor(WHITE);
        for (int i = 0; i < 5; i++)
        {
            printf("\t\t\t  %d. %s\n", i + 1, opciones[i]);
        }
        printf("\n\t\t  Ingrese una opcion: ");
        scanf("%d", &Op);
        switch (Op)
        {
        case 1:
            system("cls");
            registroSocio();
            break;
        case 2:
            system("cls");
            regActividadesSocio();
            break;
        case 3:
            system("cls");
            listaSocios();
            break;
        case 4:
            system("cls");
            listaPagoSocios();
            break;
        case 5:
            band = false;
            b = false;
            break;
        default:
            system("cls");
            textcolor(RED);
            printf("\n\n\n\t\t\t\t\tError, respuesta invalida...");
            textcolor(WHITE);
            system("pause>nul");
        }
    } while (band);
    system("cls");
    textcolor(BLUE);
    printf("\n\n\n\n\n\t\t\t\tSe cerro el modulo de Recepcion. Adios...\n\n\n\n");
    textcolor(WHITE);
    system("pause>nul");
}

void registroSocio()
{

    Socios soc;
    FILE *arch = fopen("Socios.dat", "a+b");
	
	system("cls");
    textcolor(RED);
    printf("\n\n\t\t\t\t\t------|REGISTRO SOCIO|------\n\n");
    textcolor(WHITE);
    printf("\n\t\tINGRESE APELLIDO Y NOMBRE: ");
    fflush(stdin);
    gets(soc.apeNom);
    printf("\n\t\tDOMICILIO: ");
    gets(soc.domicilio);
    printf("\n\t\tINGRESE DNI: ");
    scanf("%d", &soc.dni);
    printf("\n\t\tFECHA DE INGRESO:");
    printf("\n\t\tDIA: ");
    scanf("%d", &soc.fechaDeIngreso.dia);
    printf("\n\t\tMES: ");
    scanf("%d", &soc.fechaDeIngreso.mes);
    printf("\n\t\tA%cO: ", 165);
    scanf("%d", &soc.fechaDeIngreso.anio);
    printf("\n\t\tINGRESE EDAD: ");
    scanf("%d", &soc.edad);
    printf("\n\t\tINGRESE ALTURA (EN METROS): ");
    scanf("%f", &soc.altura);
    fflush(stdin);
    printf("\n\t\tINGRESE PESO: ");
    scanf("%f", &soc.peso);
    printf("\n\t\tINDICACION MEDICA: ");
    fflush(stdin);
    gets(soc.indicacionMedica);
    printf("\n\t\tNUMERO DE SOCIO: ");
    scanf("%d", &soc.nroSocio);
    fseek(arch, sizeof(Socios), SEEK_END);
    fwrite(&soc, sizeof(Socios), 1, arch);
    textcolor(GREEN);
    printf("\n\n\n\n\t\t\tSocio registrado exitosamente...");
    textcolor(WHITE);
    system("pause>nul");
    fclose(arch);
}

void regActividadesSocio()
{
    FILE *arch = fopen("Actividades.dat", "r+b");
    FILE *arch1 = fopen("Entrenador.dat", "r+b");

    Entrenador ent;
    actividad act;
    Socios soc;

	system("cls");
    textcolor(RED);
    printf("\n\n\t\t\t\t------|REGISTRO ACTIVIDAD SOCIO|------\n\n");
    textcolor(WHITE);
    
    int nroSocio, cont = 0, op;
    printf("\n\t\t\tINGRESE NUMERO DE SOCIO: ");
    scanf("%d", &nroSocio);

    rewind(arch);
    fread(&act, sizeof(actividad), 1, arch);
    while (!feof(arch))
    {

        rewind(arch1);
        fread(&ent, sizeof(Entrenador), 1, arch1);
        while (!feof(arch1))
        {
            if (act.legEntrador == ent.legajoEntrenador)
            {

                break;
            }
            fread(&ent, sizeof(Entrenador), 1, arch1);
        }
        printf("\n\n\t%d- %s con %s, a la hora %d \n", cont + 1, act.nomActividad, ent.apeNom, act.hora);
        for (int i = 0; i < 50; i++)
        {
            if (act.nroSocios[i] == 0)
            {
                break;
            }
            printf("\t\t%d", act.nroSocios[i]);
        }

        cont++;
        fread(&act, sizeof(actividad), 1, arch);
    }
    printf("\n\n\t\tIngrese la opcion: ");
    scanf("%d", &op);
    act.cantSocios++;
    rewind(arch);
    fread(&act, sizeof(actividad), 1, arch);
    while (!feof(arch))
    {
        if (act.key == op)
        {
            int x = arrLibre(act);
            act.nroSocios[x] = nroSocio;
            act.cantSocios++;
            break;
        }
        fread(&act, sizeof(actividad), 1, arch);
    }

    fseek(arch, -sizeof(actividad), SEEK_CUR);
    fwrite(&act, sizeof(actividad), 1, arch);
    fclose(arch);
    fclose(arch1);
}

int arrLibre(actividad act)
{
    if (act.nroSocios[0] == 0)
    {
        return 0;
    }

    for (int i = 0; i < 50; i++)
    {
        if (act.nroSocios[i] == 0)
        {
            return i;
        }
    }
}

void listaSocios()
{

    FILE *arch = fopen("Socios.dat", "r+b");
    FILE *arch1 = fopen("Actividades.dat", "r+b");
    FILE *arch2 = fopen("Entrenador.dat", "r+b");
    Socios soc;
    actividad act;
    Entrenador ent;
    int cont = 0;
    
    system("cls");
    textcolor(RED);
    printf("\n\n\t\t\t\t\t---- | Listado de Socios | ----");
    textcolor(WHITE);
    rewind(arch);
    fread(&soc, sizeof(Socios), 1, arch);
    while (!feof(arch))
    {
        if (cont == 2)
        {
            printf("\n\n\t\tPRESIONE ENTER PARA CONTINUAR VIENDO SOCIOS...");
            system("pause>nul");
            system("CLS");
            cont = 0;
            textcolor(RED);
    		printf("\n\n\t\t\t\t\t---- | Listado de Socios | ----\n");
    		textcolor(WHITE);
        }
        printf("\n\t\tNUMERO DE SOCIO: %d", soc.nroSocio);
        printf("\n\t\tAPELLIDO Y NOMBRE: %s", soc.apeNom);
        printf("\n\t\tDOMICILIO: %s", soc.domicilio);
        printf("\n\t\tDNI: %d", soc.dni);
        printf("\n\t\tEDAD: %d", soc.edad);
        printf("\n\t\tFECHA DE INGRESO: %d/%d/%d", soc.fechaDeIngreso.dia, soc.fechaDeIngreso.mes, soc.fechaDeIngreso.anio);
        printf("\n\t\tALTURA: %.2f METROS", soc.altura);
        printf("\n\t\tPESO: %.2f KG", soc.peso);
        printf("\n\t\tINDICACION MEDICA: %s", soc.indicacionMedica);
        printf("\n\t\tACTIVIDAD QUE DESARROLLA: ");
        rewind(arch1);
        fread(&act, sizeof(actividad), 1, arch1);
        while (!feof(arch1))
        {
            for (int i = 0; i < 50; i++)
            {
                if (act.nroSocios[i] == soc.nroSocio)
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
                    printf(" %s con %s a las %dhs. -|-", act.nomActividad, ent.apeNom, act.hora);
                    break;
                }
            }
            fread(&act, sizeof(actividad), 1, arch1);
        }
        printf("\n\n-----------------------------------------------------------------------------------------------");
        fread(&soc, sizeof(Socios), 1, arch);
        cont++;
    }
    system("pause>nul");
    fclose(arch);
}

void listaPagoSocios()
{

    FILE *arch = fopen("Socios.dat", "r+b");

    Socios soc;
    
    system("cls");
	textcolor(RED);
    printf("\n\n\t\t\t\t\t------|LISTADO PAGO DE SOCIOS|------");
    textcolor(WHITE);
    rewind(arch);
    fread(&soc, sizeof(Socios), 1, arch);
    while (!feof(arch))
    {
        printf("\n\n\t\t\t\t\tAPELLIDO Y NOMBRE: %s", soc.apeNom);
        printf("\n\n\t\t\t\t\tDNI DEL SOCIO: %d", soc.dni);
        printf("\n\n\t\t\t\t\tFECHA DE INGRESO: %d/%d/%d", soc.fechaDeIngreso.dia, soc.fechaDeIngreso.mes, soc.fechaDeIngreso.anio);
        printf("\n\n\t\t-----------------------------------------------------------------------------------------------");
        fread(&soc, sizeof(Socios), 1, arch);
    }
    system("pause>nul");
}
