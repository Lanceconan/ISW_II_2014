<?php

class PaisesController extends BaseController {
    
    public function showHome(){
            return View::make('paises.home');
    }
    
    public function showListar(){
        $paises = Paises::all();    
        return View::make('paises.listar') -> with ('paises',$paises);
    }
    
    public function showDetalles(){
        $paises = Paises::all();    
        return View::make('paises.detalles') -> with ('paises',$paises);
    }
    
    public function newPais()
    {
        return View::make('paises.nuevo');
    } 
    
    public function createPais(){   
        $inputs = Input::All();               
        
        $reglas = array(
            'nuevo_nombre' => 'required|min:3',
            'nuevo_capital' => 'required|min:3'
        );
        
        $mensajes = array(
            "required" => "este campo es obligatorio",
            "min" => "debe tener como minimo 3 caracteres"
        );
        
        $validar = Validator::make($inputs, $reglas, $mensajes);
        
        if ($validar->fails()) {
            return Redirect::back()->withErrors($validar);
        } else {
            $pais = new Paises();
            $pais->Nombre = $inputs["nuevo_nombre"];
            $pais->Capital = $inputs["nuevo_capital"];
            $pais->Habitantes = $inputs["nuevo_habitantes"];
            $pais->save();
            
            Session::flash('mensaje', 'El registro ha sido ingresado exitosamente');
            return Redirect::to('./listar'); 
        }        
    }
    
    public function deletePais() {
        $input = Input::All();
        
        print $input["id"];
        
        $pais = Paises::find($input["id"]);
        if(is_null($pais)){
            return Redirect::to('../');
        }else{
            $pais->delete();
            return Redirect::to('./detalles');
        }
    }
    
    public function eliminarPais($id=null) {
        $pais = Paises::find($id);
        $pais->delete();
        return Redirect::to('./detalles');
    }
    
    public function editPais($id=null)
    {             
        $pais = Paises::find($id);
        if (is_null($pais)) {
            App::abort(404);
        }
        return View::make('paises.modificar') -> with ('pais',$pais);
    } 
    
    public function changePais() {
        $inputs = Input::All();        
        
        $reglas = array(
            'nuevo_nombre' => 'required|min:3',
            'nuevo_capital' => 'required|min:3'
        );
        
        $mensajes = array(
            "required" => "este campo es obligatorio",
            "min" => "debe tener como minimo 3 caracteres"
        );
        
        $validar = Validator::make($inputs, $reglas, $mensajes);
        
        if ($validar->fails()) {
            return Redirect::back()->withErrors($validar);
        } else {
            $pais = Paises::find($inputs["id"]);
            $pais->Nombre = $inputs["nuevo_nombre"];
            $pais->Capital = $inputs["nuevo_capital"];
            $pais->Habitantes = $inputs["nuevo_habitantes"];
            $pais->save();
            
            Session::flash('mensaje', 'El registro ha sido ingresado exitosamente');
            return Redirect::to('./listar'); 
        }  
    }
}
