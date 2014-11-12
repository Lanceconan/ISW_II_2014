@extends('layouts.master')

@section('inicio_vista')
    <div class="col-lg-12">
        <h1 class="page-header">
            Tabla Detallada
        </h1>
        <ol class="breadcrumb">
            <li>
                <i class="fa fa-dashboard"></i>  <a href="./">Inicio</a>
            </li>
            <li class="active">
                <i class="fa fa-wrench"></i> Tabla con modificacion directa.
            </li>
        </ol>
    </div>
@stop

@section('mostrar')
    <div>
        @if(Session::has('mensaje'))
        <p style="color: red"><strong>{{Session::get('mensaje')}}</strong></p>
        @endif
        <!--<h2>Paises.</h2>-->
        <div class="table-responsive">
            <table class="table table-hover table-striped">                
                <thead>
                    <tr>
                        <th>ID</th>
                        <th>Nombre</th>
                        <th>Capital</th>
                        <th>Habitantes</th>
                        <th></th>
                        <th></th>
                    </tr>
                </thead>
                <tbody>
                    @foreach($paises as $pais)
                    <form>
                    <tr>
                        <td><input id="id" name="id" class="form-control" readonly="true" value="{{$pais->id}}" ></td>
                        <td><input id="nombre" name="nombre" class="form-control" readonly="true" value="{{$pais->Nombre}}" onkeypress="return validatext(event,'1')"></td>
                        <td><input id="capital" name="capital" class="form-control" readonly="true" value="{{$pais->Capital}}" onkeypress="return validatext(event,'1')"></td>
                        <td><input id="habitaciones" name="habitantes" class="form-control" readonly="true" value="{{$pais->Habitantes}}" onkeypress="return validatext(event,'2')"></td>
                        <td><button type="submit" class="btn btn-default" formaction="./editar{{$pais->id}}" >Modificar Datos</button></td>
                        <td><button type="submit" class="btn btn-default" formmethod="post" formaction="./eliminar">Eliminar Dato</button></td>
                    </tr>
                    </form>
                    @endforeach
                </tbody>                
            </table>
        </div>
    </div>
@stop

