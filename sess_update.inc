<?
// обновление длительности сессии при заходе на любую страницу сайта
function updatesession()
{ // обновление длительности сессии
global $tabusers;
global $tablog;
global $StartTimeCookie;
global $UserLogNumCookie;
global $UserIdCookie;
global $StartIPCookie;
global $UserAccCodeCookie;

$tablog='log';
$tabusers='users';

  if (isset($UserIdCookie))
  {  
   $id = $UserIdCookie;
   $LogNum = $UserLogNumCookie; // номер записи в журнале
   $StartT = $StartTimeCookie;  // время начала сессии
// echo "Начало сеанса ".$StartT;
// echo "LogNum=".$LogNum;

$EndT=time();
$T = date( "Y-m-d  H:i:s",$EndT ); // время конца сессии

$difft=$EndT-$StartT;  // длительность сессии на данный момент, без окончания сессии

//echo "UserIdCookie=".$UserIdCookie;
//echo "<br> с момента начала сессии difft=".$difft;
$res  = db_query( "select connect_time from $tablog where num=$LogNum" );
list($prev_connect_time) = db_fetch_row( $res );  
//echo "<br> предыдущее отмеченное время соединения prev_connect_time=".$prev_connect_time;
// $prev_connect_time предыдущее отмеченное время соединения
// обновляем в журнале время выхода из сессии и длительность сессии
$res  = db_query("update $tablog set output_time='$T',connect_time='$difft' where num=$LogNum");
// считаем, сколько времени прошло с предыдущей фиксации длительности сессии
$difft = $difft - $prev_connect_time;
//echo "<br> в таблицу юзеров прибавляем difft=".$difft;
// на эту величину увеличиваем суммарное время соединения в таблице пользователей
$res  = db_query( "select sum_time from $tabusers where id=$id" );
list($sum_time) = db_fetch_row( $res );
$sum_time=$sum_time+$difft;
$res  = db_query("update $tabusers set sum_time='$sum_time' where id=$id");
 }
// else
// { echo "нет регистрации - нет обновления";
// } 

}
?>