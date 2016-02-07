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

    // code à implémenter... Memset de la structure client
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
        //code à implémenter désactiver le bouton recevoir
        break;
    case WM_COMMAND:
        NotificationControle(hwnd,message,wParam,lParam);
        break;
    case WM_CLOSE:
        MessageBox(hwnd,"Click fermeture fentre !!","",MB_OK);
        // code à implémenter... fermer le fichier
        //code à implémenter... arreter le socket serveur
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
        //code à implémenter.... activer le bouton recevoir
        //code à implémenter.... désactiver le bouton acceptconnexion
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
        // écrire le contenu de bufferReception dans le contrôle edit messagerecu
        // copier bufferReception dans la variable MsgEnvoye de type client
        //ecrire la structure dans le fichier

        MessageBox(hwnd,bufferReception,"",MB_OK);
        break;
    }
}
