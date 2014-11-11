<?php

/*
|--------------------------------------------------------------------------
| Application Routes
|--------------------------------------------------------------------------
|
| Here is where you can register all of the routes for an application.
| It's a breeze. Simply tell Laravel the URIs it should respond to
| and give it the Closure to execute when that URI is requested.
|
*/

Route::get('/asd', function()
{
	return View::make('hello');
});

Route::get('/', 'PaisesController@showHome');
Route::get('/listar', 'PaisesController@showListar');
Route::get('/detalles', 'PaisesController@showDetalles');
Route::get('/nuevo', 'PaisesController@newPais');
Route::post('/crear','PaisesController@createPais');
Route::post('/eliminar','PaisesController@deletePais');
Route::get('/editar{id}','PaisesController@editPais');
Route::post('/guardarcambio','PaisesController@changePais');
