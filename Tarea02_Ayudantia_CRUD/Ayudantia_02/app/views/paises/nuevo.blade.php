@extends('layouts.master')

@section('inicio_vista')
    <div class="col-lg-12">
        <h1 class="page-header">
            Crear Pais
        </h1>
        <ol class="breadcrumb">
            <li>
                <i class="fa fa-dashboard"></i>  <a href="./">Inicio</a>
            </li>
            <li class="active">
                <i class="fa fa-pencil-square"></i> Crear nuevo registro.
            </li>
        </ol>
    </div>
@stop

@section('mostrar')

    <div class="col-lg-6">
        @if(Session::has('mensaje'))      
        <h2 style="color: red;">{{ Session::get('mensaje') }}</h2>       
        @endif
        <form action="./crear" method="post">
            <div class="form-group">
                <label>Nombre de Pais</label>
                <input id="nuevo_nombre" name="nuevo_nombre" autocomplete="false" class="form-control" onkeypress="return validatext(event,'1')" required="true">
                <p class="help-block">Ingrese nombre del pais que desea crear.</p>
            </div>
            <div class="form-group">
                <label>Capital de Pais</label>
                <input id="nuevo_capital" name="nuevo_capital" autocomplete="false" class="form-control" onkeypress="return validatext(event,'1')" required="true">
                <p class="help-block">Ingrese nombre de la capital del pais a crear.</p>
            </div>
            <div class="form-group">
                <label>Habitantes</label>
                <input id="nuevo_habitantes" name="nuevo_habitantes" class="form-control" onkeypress="return validatext(event,'2')" required="true">
                <p class="help-block">Ingrese cantidad de habitantes del pais a crear.</p>
            </div>
            <button type="reset" class="btn btn-default">Cancelar Datos</button>
            <button type="submit" class="btn btn-default" formaction="./crear" method="POST">Crear Pais</button>
        </form>        
    </div>
@stop
