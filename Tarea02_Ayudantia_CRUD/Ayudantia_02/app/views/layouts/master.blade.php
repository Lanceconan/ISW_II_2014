<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Trabajo ISW - Ayudantia 02</title>

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="css/sb-admin.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="font-awesome-4.1.0/css/font-awesome.min.css" rel="stylesheet" type="text/css">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>

<body>

    <div id="wrapper">

        <!-- Navigation -->
        <nav class="navbar navbar-inverse navbar-fixed-top" role="navigation">
            <!-- Brand and toggle get grouped for better mobile display -->
            <div class="navbar-header">                
                <a class="navbar-brand" href="./">Trabajo de Ingenieria de Software - Ayudantia 02</a>
            </div>
            <!-- Top Menu Items -->
            <ul class="nav navbar-right top-nav">
                <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-user"></i> Integrantes. <b class="caret"></b></a>
                    <ul class="dropdown-menu">
                        <li>
                            <a href="#"><i class="fa fa-fw fa-user"></i> Daniel Leiva</a>
                        </li>
                        <li>
                            <a href="#"><i class="fa fa-fw fa-user"></i> Daniel Gutierrez</a>
                        </li>
                        <li>
                            <a href="#"><i class="fa fa-fw fa-user"></i> Ernesto Rojas</a>
                        </li>
                    </ul>
                </li>
            </ul>
            <!-- Sidebar Menu Items - These collapse to the responsive navigation menu on small screens -->
            <div class="collapse navbar-collapse navbar-ex1-collapse">
                <ul id="menu_lateral" class="nav navbar-nav side-nav" onclick="">
                    <li id="lateral_inicio" class="active" onclick="return prueba('lateral_inicio');">
                        <a href="./"><i class="fa fa-fw fa-dashboard"></i> Inicio</a>
                    </li>
                    <li id="lateral_listar" onclick="return prueba('lateral_listar');">
                        <a href="./listar"><i class="fa fa-fw fa-table"></i> Listar Paises</a>
                    </li>
                    <li id="lateral_nuevo" onclick="return prueba('lateral_nuevo');">
                        <a href="./nuevo"><i class="fa fa-fw fa-pencil-square"></i> Nueva Informacion</a>
                    </li>
                    <li>
                        <a href="#"><i class="fa fa-fw fa-edit"></i> Modificar Informacion</a>
                    </li>
                    <li id="lateral_detalles" onclick="return prueba('lateral_detalles');">
                        <a href="./detalles"><i class="fa fa-fw fa-wrench"></i> Tabla Detallada</a>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </nav>

        <div id="page-wrapper">

            <div class="container-fluid">

                <!-- Page Heading -->
                <div class="row">                    
                    
                        @yield('inicio_vista')
                                       
                </div>
                <!-- /.row -->
                <div>
                        @yield('mostrar')
                </div>
            </div>
            <!-- /.container-fluid -->

        </div>
        <!-- /#page-wrapper -->

    </div>


    <!-- /#wrapper -->

    <!-- jQuery Version 1.11.0 -->
    <script src="js/jquery-1.11.0.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="js/bootstrap.min.js"></script>
    <!-- Propios JavaScript -->
    <script src="js/validaciones.js"></script>
    <!-- Test JavaScript -->
    <script>
        function prueba(id){
            $("#lateral_inicio").class("inactive");
            $("#lateral_listar").class("inactive");
            $("#lateral_nuevo").class("inactive");
            $("#lateral_detalles").class("inactive");
            $("#"+id).class("active");            
        };
    </script>
    
</body>

</html>