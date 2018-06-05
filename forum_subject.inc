

<p class=ur1>ФОРУМ АИОР</p>

<?

global $UserAccCodeCookie;

//echo "Пользователь=";
//echo $UserIdCookie;
//echo "Логин=";
//echo $UserLoginCookie;
//echo "Доступ=";
//echo $UserAccCodeCookie;

$alenlimit = 15;  // макс длина имени автора в таблице списка тем

$tabusers='users';
$tabsubj='raee_subject';
$tabforum='raee_forum';

  
if ((isset($UserIdCookie)) and !(isset($out)))
{  // пользователь зарегистрирован
   $id = $UserIdCookie;
   $acc = $UserAccCodeCookie;
   $res  = db_query("select name,work from $tabusers where id=$id");
   $rows = db_num_rows( $res );
   if ($rows > 0) {
      list($name,$work) = db_fetch_row( $res );
      $username = $name;
//      echo $username;
   }
}

$pagesize = 25;
if (!isset($pb)) {$pb=0;};
$pe = $pb + $pagesize;
$curpage = $pb/$pagesize + 1;

//if (($p == '') & ($sp == '')) { $p=1;}   //не будем определять нач раздел Начальный раздел - первый

?>


<form name="newsubj" method="post" action="subject_add.php">
<table border=0 cellpadding=3 cellspacing=0>
<tr>
<td align=center>Название новой темы:</td>
<td align=center>Ваше имя:</td>
<td>&nbsp;</td>
</tr>
<tr bgcolor=#F0F0F0>
<td align=center>
<input class=inp name="subjname" type=text size=50 maxlength=200>
</td>
<td align=center>
<?
if (isset($username)) {
echo "<input class=inp name=\"autname_vis\" value=\"".$username."\" type=text size=20 maxlength=70 disabled>";
echo "<input type=hidden name=\"autname\" value=\"".$username."\">";
}
else
{
   echo "<input class=inp name=\"autname\" type=text size=20 maxlength=70>";
}
?>
<input type="hidden" name="s" value="<? echo $s;?>" >
</td>
<td align=center><input type=submit value="Создать новую тему" class="map" onClick="return CheckInnNewSubjForm()">
</td>
</tr>
</table>
</form>




<table border=0 cellpadding=0 cellspacing=0 width=98% bgcolor=#FFFFFF>
<tr>
<td valign=top>
<!-- список тем форума -->

<?


$c=true;



$parttit = '';
// --------------- темы
   $res  = db_query( "select * from $tabsubj where numsubject>0" );
   $rows = db_num_rows( $res );
   $allrows = $rows;
   $qpages=ceil($allrows/$pagesize);

//echo "allrows=".$allrows;
//echo "qpages=".$qpages;
//echo "pb=".$pb;
//echo "pe=".$pe;
//echo "curpage=".$curpage;


   for( $i = 0; $i < $rows; $i++ )
   {
      list($nums,$subject,$c_a,$author,$sdatetime,$e_subject) = db_fetch_row( $res );
      $num[$i] = $nums;
      $subj[$i] = $subject;
      $dcreate[$i] = $sdatetime;
$subjauthor[$i] = $author;

//echo $num[$i];
//echo "/"; 
//echo $dcreate[$i]; 
   }
   while ( list( $i, $subject ) = each( $subj ) ) {
     $nums = $num[$i];
     $sdatetime = $dcreate[$i];

     $res  = db_query( "select author, mdatetime from $tabforum where numsubject=$nums order by mdatetime desc");
//     $res  = db_query( "select mdatetime from $tabforum where numsubject=$nums order by mdatetime desc");
     $allmesinsubj = db_num_rows( $res ); // всего сообщений в теме
     list($l_author,$mdatetime) = db_fetch_row( $res );  // автор и дата последнего сообщения в теме
//     list($mdatetime) = db_fetch_row( $res );  // дата последнего сообщения в теме

     $allmess[$i] = $allmesinsubj;
if ( $allmess[$i] > 0 ) 
{ $lastdate[$i] = $mdatetime; $lastauthor[$i] = $l_author;} else { $lastdate[$i] = $dcreate[$i]; $lastauthor[$i] = '';}
   }

   arsort($lastdate);  // сортировка по дате посл. сообщения, в обр. порядке
   reset($lastdate);
   list( $n, $mdatetime ) = each( $lastdate );
   if ($s == '') { $s = $n;};   //если текущая тема не определена, то первая тема по отсортированному списку
   reset($lastdate);

   // если была определена текущая тема $sr (возвратились из forum_s), 
   // то вычисляем страницу, на которой находится эта тема
if (isset($sr)) {
   $n = 0;
   while ( list( $n, $numsubj ) = each( $num ) ) {
     if ($numsubj == $sr) {
//       echo 'Номер для темы '.$numsubj.'='.$n; 
       break;
     }
   }
     $number = $n;
     // найден номер для темы, ищем страницу для этого номера
     $ind = 0;
     while ( list( $n, $mdatetime ) = each( $lastdate ) ) {
       if ($n == $number) {break;}
       $ind = $ind+1;
     }
//     echo 'Номер п/п в lastdate '.$ind; 
     reset($lastdate);
     
     $pb = floor($ind/$pagesize)*$pagesize;
     $pe = $pb + $pagesize;
     $curpage = $pb/$pagesize + 1;
//echo "pb=".$pb;
//echo "pe=".$pe;
//echo "curpage=".$curpage;
     $s = $sr;
     $sr='';
}

echo "<table cellspacing=3 border=0 cellpadding=2 width=750>";
echo "<tr><td colspan=5>";
require( "s_navigate.inc" );
echo "</td></tr>";
echo "<tr bgcolor=#F0F0F0 align=center valign=middle><td width=110><p class=dbtit>Дата<br>обновления</p></td><td width=400><p class=dbtit>Тема</p></td><td width=60><p class=dbtit>Сооб-<br>щений<br>в теме</p></td><td width=110><p class=dbtit>Дата создания</p></td><td width=80><p class=dbtit>Автор темы</p></td></tr>";
// с автором темы и сообщ, автора сообщ пока не ставим
//echo "<tr bgcolor=#F0F0F0 align=center valign=middle><td width=110><p class=dbtit>Дата<br>обновления</p></td><td width=400><p class=dbtit>Тема</p></td><td width=60><p class=dbtit>Сооб-<br>щений<br>в теме</p></td><td width=80><p class=dbtit>Автор<br>последнего<br>сообщения</p></td><td width=110><p class=dbtit>Дата создания</p></td><td width=80><p class=dbtit>Автор темы</p></td></tr>";
// без авторов темы и сообщ
//echo "<tr bgcolor=#F0F0F0 align=center valign=middle><td width=110><p class=dbtit>Дата<br>обновления</p></td><td width=400><p class=dbtit>Тема</p></td><td width=80><p class=dbtit>Сообщений<br>в теме</p></td><td width=110><p class=dbtit>Дата создания</p></td></tr>";


      if ($code == $p) {echo "<tr bgcolor=#D3E6FF>"; $parttit = $namepart;} else {echo "<tr>";}

   // вывод на страницу в порядке, определенном массивом lastdate,
   // но только тех тем, которые относятся к текущей странице, 
   // то есть начиная c pb
   $ind = 0;
   while ( list( $n, $mdatetime ) = each( $lastdate ) ) {
     if (($ind >= $pb) & ($ind < $pe)) {
     if ($num[$n] == $s) {echo "<tr bgcolor=#D3E6FF>";} else {
     if ($c) {echo "<tr  bgcolor=#FFFFFF>"; } else {echo "<tr bgcolor=#F0F0F0>"; }
     }
     $c=!$c;
     echo "<td align=center><p>".substr($mdatetime,0,16)."</p></td>";
     echo "<td><p class=ur2r><a href='forum_s.phtml?s=$num[$n]&pback=$pback'>$subj[$n]</a></td>";

     echo "<td><p style=color:#700000 align=center><b>$allmess[$n]</b></td>";
// автор последнего сообщения, пока не ставим
//  if (strlen($lastauthor[$n]) > $alenlimit) { $lastauthor[$n] = substr($lastauthor[$n],0,14).'...'; } 
//   echo "<td><p>".$lastauthor[$n]."</p></td>";
     echo "<td align=center><p>".substr($dcreate[$n],0,16)."</p></td>";
     if (strlen($subjauthor[$n]) > $alenlimit) { $subjauthor[$n] = substr($subjauthor[$n],0,14).'...'; } 
     echo "<td><p>".$subjauthor[$n]."</p></td></tr>";
//     echo "<td align=center><p>".substr($dcreate[$n],0,16)."</p></td></tr>";
     }
     $ind = $ind+1;
   }

// ----------- темы - end


if ( $allrows > $pagesize ) {
echo "<tr><td colspan=5>";
require( "s_navigate.inc" );
echo "</td></tr>";
}
echo "</table>";

?>


</td>

</tr>
</table>



