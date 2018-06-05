<?
function noregistration()
{ // регистрация еще не пройдена, запрос имени и пароля
global $monthes;
global $sr;
global $pb;
global $searchfield;
require( "forum_before.inc" );
//  echo "регистрация еще не пройдена";
print "
<tr><td>
<p class=menu><a class=m href=\"useradd.php\">Регистрация</a></p>
</td></tr>
<tr>
<td bgcolor=#D5DCE2><img src=\"images/spacer.gif\" height=2></td>
</tr>
<tr><td>
<p class=menu>Авторизация</p>
</td></tr>
<tr>
<td bgcolor=#D5DCE2>
<table cellpadding=2 cellspacing=2 border=0>
<tr>
<form name=enter action=forum.php method=post >
<td align=right><p class=logpass>Имя:</td>
<td><input style=\"font-size:9pt\" type=text name=inputlogin size=10></td>
</tr><tr>
<td><p class=logpass>Пароль:</td>
<td><input style=\"font-size:9pt\" type=password name=inputpass size=10></td>
</tr><tr>
<td> &nbsp;</td>
<td align=center><input style=\"font-size:9pt\" type=submit value=\"вход\" onClick=\"return CheckEnter()\"></td></form>
</tr>
</table>
</td>
</tr>
<tr>
<td bgcolor=#D5DCE2><img src=\"images/spacer.gif\" height=5></td>
</tr>
";
require( "forum_after.inc" );
}

if( !$inlib ) { include( "lib.inc" ); db_connect(); }

include("auto.inc");
$tabusers='users_tomsk';
$tablog='log_tomsk';  // журнал
$reg_true = false;
$flcreatelog = false;  //по умолчанию - не делать новой записи в журнале 
$access_code=0;   //по умолчанию - код доступа - пользовательский

if (isset($out))
{ 
   closesession();
   // стирание кук в головной директории
   echo "<SCRIPT LANGUAGE=JavaScript>location.href = \"close_forum.php\"; </SCRIPT>";
    noregistration();
}
else
{
   if (isset($UserIdCookie))
   {  // регистрация уже была успешно проведена
     $id = $UserIdCookie;
     $inputlogin = $UserLoginCookie;
     $StartT = $StartTimeCookie;
     yesregistration(0);
   }
   else
   {
     if (isset($inputlogin)) 
     {
$inputlogin = trim($inputlogin);
$inputpass = trim($inputpass);
// Есть ли в базе регистрационное имя и пароль?
$usl='"'.$inputlogin.'"';
$res  = db_query( "SELECT id,pass,name,last_date,q_attantion,access_code from $tabusers where login like ".$usl );
$qlogin = db_num_rows( $res );
  if ($qlogin > 0) 
  {  // user зарегистрирован, проверяем пароль
     list($id,$pass,$name,$last_date,$q_attantion,$access_code) = db_fetch_row( $res );
     if ($inputpass == $pass)
     {  
        $reg_true = true; 
     }
     else {  //  неверный пароль
 echo "<SCRIPT LANGUAGE=\"JavaScript\" TYPE=\"text/javascript\"> alert(\"Пароль для пользователя ".$inputlogin." неверен\"); </SCRIPT>";

     }
  } 
  else  {  // нет такого usera
 echo "<SCRIPT LANGUAGE=\"JavaScript\" TYPE=\"text/javascript\"> alert(\"Пользователь с именем ".$inputlogin." не зарегистрирован\"); </SCRIPT>";
  }
//конец веточки повторного входа на страницу
}

if ($reg_true)
{ // регистрация успешно пройдена
  $ut=time();
  $UserLogNum=0;
  $var="REMOTE_ADDR";
  $ip=getenv($var);

echo "<SCRIPT LANGUAGE=JavaScript>location.href = \"setcook_forum.php?id=$id&inputlogin=$inputlogin&access_code=$access_code\"; </SCRIPT>";


  $StartT=$ut;
   $flcreatelog=true;   // при регистрации сделать запись в журнале
   yesregistration(1);

//   ----------------------------- не получится, только через setcookie в другом модуле  
//   $UserLogNumCookie = $UserLogNum; // запомнить в куке номер записи в журнале

 echo "<SCRIPT LANGUAGE=JavaScript>location.href = \"savcook.php?n=$UserLogNum&pback=$pback\"; </SCRIPT>";

}
else { // регистрация еще не пройдена
    noregistration();
}

} // конец else на проверку кука и уже проведенной ранее авторизации

} // конец else if по отсоединению пользователя

include("sess_update.inc");
updatesession();   // обновляем время сессии, если она была открыта

?>

