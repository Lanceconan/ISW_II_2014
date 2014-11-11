@extends('layouts.master')

@section('inicio_vista')
    <div class="col-lg-12">
        <h1 class="page-header">
            Inicio
        </h1>
        <ol class="breadcrumb">
            <li>
                <i class="fa fa-dashboard"></i>  <a href="./">Inicio</a>
            </li>
            <li class="active">
                <i class="fa fa-info"></i> Introduccion.
            </li>
        </ol>
    </div>
@stop

@section('mostrar')
    <div class="col-lg-12">
        <h5 class="lead">Trabajo de Ayudantia de la asignatura Ingenieria de Software.<br>
            Desarrollo del proyecto mediante el Framework Laravel.</h5>
    </div>
@stop