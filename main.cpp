#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
#include "server.h"


HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    SOCKET sock = init();
    f = fopen("annuaireUfip.txt", "a");

    // code � impl�menter... Memset de la structure client
    DialogBox(hInstance, "MyDialog", NULL, DialogProc);
    return 0;
}
//Et auss une fonction qui va intercepter les messages
INT_PTR CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM
                            wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_INITDIALOG:
        SetDlgItemText(hwnd, MSGCONNEXION,tmpBuffer );
        EnableWindow( GetDlgItem( hwnd, ID_BTN_ENVOI ), FALSE);
        //code � impl�menter d�sactiver le bouton recevoir
        break;
    case WM_COMMAND:
        NotificationControle(hwnd,message,wParam,lParam);
        break;
    case WM_CLOSE:
        MessageBox(hwnd,"Click fermeture fentre !!","",MB_OK);
        // code � impl�menter... fermer le fichier
        //code � impl�menter... arreter le socket serveur
        finish();
        EndDialog(hwnd, 0);
        break;
    default:
        return FALSE;
    }
    return TRUE;
}
void NotificationControle(HWND hwnd,UINT message, WPARAM wParam,
                          LPARAM lParam)
{
    switch(HIWORD(wParam))
    {
    case BN_CLICKED: // cliquer sur un des boutons recevoir ou envoyer
        messageCtl((HWND)hwnd,(UINT)message,(WPARAM)wParam,(LPARAM)lParam);
        break;
    }
}
void messageCtl(HWND hwnd,UINT message, WPARAM wParam, LPARAM
                lParam)
{
    switch(LOWORD(wParam))
    {
    case ID_BTN_ACCEPTCONNEXION:
        connexion(sock);
        SetDlgItemText(hwnd, MSGCONNEXION, tmpBuffer );
        EnableWindow( GetDlgItem( hwnd, ID_BTN_ENVOI ), TRUE);
        //code � impl�menter.... activer le bouton recevoir
        //code � impl�menter.... d�sactiver le bouton acceptconnexion
        break;

    case ID_BTN_ENVOI:
        GetDlgItemText(hwnd,EDITSENDMSG,bufferEnvoi,10);
        // copier bufferenvoi dans la variable MsgEnvoye de la strucure client
        //ecrire la strucure dans le fichier
        sendfromserver();
        break;

    case ID_BTN_RECEVOIR:
        recevoir();
        // Appeler la fonction recevoir
        // �crire le contenu de bufferReception dans le contr�le edit messagerecu
        // copier bufferReception dans la variable MsgEnvoye de type client
        //ecrire la structure dans le fichier

        MessageBox(hwnd,bufferReception,"",MB_OK);
        break;
    }
}
