<? //$path = "../../"; require( $path."backpath.inc" ); ?>

<table border=0 cellpadding=0 cellspacing=0 width=90% align=center>
<tr>
<td><img src="../mimages/spacer.gif" height=10></td>
</tr>
<tr>
<td align=right><img src="../imageslogo/aior.gif">
</td>
</tr>
</table>

<table border=0 cellpadding=0 cellspacing=0 width=100% >
<tr>
<td bgcolor=#5A7DB7>
   <table border=0 cellpadding=0 cellspacing=3>
     <tr>
        <td><img src="../mimages/spacer.gif" width=10></td>
        <td><p class="cod"><a class="acod" href="<? echo $pback;?>/winn/contact.phtml">Контакты</a></p></td> 
        <td><p class="cod"><a class="acod" href="forum.phtml?pback=<? echo $pback; ?>">Форум</a></p></td> 
        <td><p class="cod"><a class="acod" href="<? echo $pback;?>/winn/map.phtml">Карта сайта</a></p></td> 
     </tr>
   </table> 
</td>
</tr>
</table>

<? 
if( !$inlib ) { include( "lib.inc" ); db_connect(); }
include("sess_update.inc");
updatesession();   // обновляем время сессии, если она была открыта
?>

<table border=0 cellpadding=5 cellspacing=0 width=100%>
  <tr>
  <td><img src="../mimages/spacer.gif" width=80></td>
