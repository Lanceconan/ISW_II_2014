@extends('layouts.master')

@section('inicio_vista')
    <div class="col-lg-12">
        <h1 class="page-header">
            Listar Paises
        </h1>
        <ol class="breadcrumb">
            <li>
                <i class="fa fa-dashboard"></i>  <a href="./">Inicio</a>
            </li>
            <li class="active">
                <i class="fa fa-table"></i> Listado simple de Paises en BBDD.
            </li>
        </ol>
    </div>
@stop

@section('mostrar')
    <div>
        @if(Session::has('mensaje'))
        <p style="color: greenyellow"><strong>{{Session::get('mensaje')}}</strong></p>
        @endif
        <!--<h2>Paises.</h2>-->
        <div class="table-responsive">
            <table class="table table-hover table-striped">
                <thead>
                    <tr>
                        <th>Nombre</th>
                        <th>Capital</th>
                        <th>Habitantes</th>
                        <th></th>
                    </tr>
                </thead>
                <tbody>
                    @foreach($paises as $pais)
                    <form>
                    <tr>
                        <td>{{$pais->Nombre}}</td>
                        <td>{{$pais->Capital}}</td>
                        <td>{{$pais->Habitantes}}</td>
                        <td><button type="submit" class="btn btn-default" formaction="./editar{{$pais->id}}" >Modificar Datos</button></td>                        
                    </tr>
                    </form>
                    @endforeach
                </tbody>
            </table>
        </div>
    </div>
@stop

<script onload="document">
    function prueba(){
        $("#lateral_inicio").class("inactive");
        $("#lateral_listar").class("active");
        $("#lateral_nuevo").class("inactive");
        $("#lateral_detalles").class("inactive");       
    };
</script>