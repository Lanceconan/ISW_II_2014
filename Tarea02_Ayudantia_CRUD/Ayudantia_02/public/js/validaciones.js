function validatext(entrada,tipo) {
    if(entrada.keyCode!=9){
            tecla = (document.all) ? entrada.keyCode : entrada.which;
        if (tecla==8) 
            return true;  
        switch (tipo){
            case '1':   patron =/[A-Za-z ,]/; break// Solo acepta letras
            case '2':   patron = /\d/; break //Solo acepta numeros
            case '3':   patron = /\w/; break //Acepta numeros y letras
            case '4':   patron = /\D/; break//No acepta numeros
            case '5':   patron = /[\d]/;  break //Solo acepta numeros
            case '6':   patron = /[\dKk]/;  break //Solo acepta numeros y K
            case '7':   patron = /[\dKk-]/;  break //Solo acepta numeros, K y guion
            case '8':   patron = /[\d-]/;  break //Solo acepta numeros y guion
        }
        dato = String.fromCharCode(tecla);
        return patron.test(dato);
    }
    else
    return true;
}