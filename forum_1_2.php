<?
function yesregistration($flf)
{ // ����������� ��������� �������
global $UserLogNum;
global $UserIdCookie;
global $StartT;
global $flcreatelog;
global $tabusers;
global $tablog;
global $id;
global $inputlogin;
global $pback;
global $username;
global $monthes;
global $sr;
global $pb;
global $searchfield;
$path = ""; require( $path."forum_before.inc" );


// ����� ���������, ����� ���������... -> � �� 
$ut=$StartT; 
$T = date( "Y-m-d  H:i:s", $ut );
$var="REMOTE_ADDR";
$ip=getenv($var);


   // ���� ������������� �����������, � �� refresh �������� � ������������, 
   // �� ��������� ����� ��������� � ��
   $res  = db_query( "SELECT name,q_attantion from $tabusers where id=$id" );
   list($username,$q_attantion) = db_fetch_row( $res );
//   echo "������� ����� ���������= $q_attantion<br>";
//echo "$flf <br>";
if ( $flf == 1) {
   $q_attantion = $q_attantion + 1;
   $res  = db_query("update $tabusers set q_attantion='$q_attantion',last_date='$T', ip='$ip' where id=$id");
}
   if ($flcreatelog)
   {
   $res  = db_query("insert into $tablog values('$id','$T',0,0,'$ip',0)");
   $UserLogNum = db_insert_id();   // ����� ������ � �������
   }
   //echo "UserLogNum=".$UserLogNum;

print "
<tr><td bgcolor=#D5DCE2>
<p class=logpass align=center>�����������<br>����������:<br><font color=#000000>$inputlogin</font></p>
</td></tr>
<tr>
<td bgcolor=#D5DCE2><img src=\"images/spacer.gif\" height=5></td>
</tr>
<tr><td>
<p class=menu><a class=m href=\"userupdate.php\">��������� ��������������� ������</a></p>
</td></tr>
<tr>
<td bgcolor=#D5DCE2><img src=\"images/spacer.gif\" height=2></td>
</tr>
<tr><td>
<p class=menu><a class=m href=\"forum.php?out=1\">������ �����������</a></p>
</td></tr>
<tr>
<td bgcolor=#D5DCE2><img src=\"images/spacer.gif\" height=2></td>
</tr>
";

if ($UserIdCookie<2 )
{
print"
<tr><td>
<p class=menu><a class=m href=\"stat.php\">����������</a></p>
</td></tr>
<tr>
<td bgcolor=#D5DCE2><img src=\"images/spacer.gif\" height=2></td>
</tr>
";
}
require( "forum_after.inc" );
}


if( !$inlib ) { include( "lib.inc" ); db_connect(); }

include("auto.inc");
$tabusers='users_tomsk';
$tablog='log_tomsk';  // ������
$reg_true = false;
$flcreatelog = false;  //�� ��������� - �� ������ ����� ������ � ������� 
$access_code=0;   //�� ��������� - ��� ������� - ����������������

if (isset($out))
{ 
   closesession();
   // �������� ��� � �������� ����������
   echo "<SCRIPT LANGUAGE=JavaScript>location.href = \"close_forum.php\"; </SCRIPT>";
    noregistration();
}
else
{
   if (isset($UserIdCookie))
   {  // ����������� ��� ���� ������� ���������
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
// ���� �� � ���� ��������������� ��� � ������?
$usl='"'.$inputlogin.'"';
$res  = db_query( "SELECT id,pass,name,last_date,q_attantion,access_code from $tabusers where login like ".$usl );
$qlogin = db_num_rows( $res );
  if ($qlogin > 0) 
  {  // user ���������������, ��������� ������
     list($id,$pass,$name,$last_date,$q_attantion,$access_code) = db_fetch_row( $res );
     if ($inputpass == $pass)
     {  
        $reg_true = true; 
     }
     else {  //  �������� ������
 echo "<SCRIPT LANGUAGE=\"JavaScript\" TYPE=\"text/javascript\"> alert(\"������ ��� ������������ ".$inputlogin." �������\"); </SCRIPT>";

     }
  } 
  else  {  // ��� ������ usera
 echo "<SCRIPT LANGUAGE=\"JavaScript\" TYPE=\"text/javascript\"> alert(\"������������ � ������ ".$inputlogin." �� ���������������\"); </SCRIPT>";
  }
//����� ������� ���������� ����� �� ��������
}

if ($reg_true)
{ // ����������� ������� ��������
  $ut=time();
  $UserLogNum=0;
  $var="REMOTE_ADDR";
  $ip=getenv($var);

echo "<SCRIPT LANGUAGE=JavaScript>location.href = \"setcook_forum.php?id=$id&inputlogin=$inputlogin&access_code=$access_code\"; </SCRIPT>";


  $StartT=$ut;
   $flcreatelog=true;   // ��� ����������� ������� ������ � �������
   yesregistration(1);

//   ----------------------------- �� ���������, ������ ����� setcookie � ������ ������  
//   $UserLogNumCookie = $UserLogNum; // ��������� � ���� ����� ������ � �������

 echo "<SCRIPT LANGUAGE=JavaScript>location.href = \"savcook.php?n=$UserLogNum&pback=$pback\"; </SCRIPT>";

}
else { // ����������� ��� �� ��������
    noregistration();
}

} // ����� else �� �������� ���� � ��� ����������� ����� �����������

} // ����� else if �� ������������ ������������

include("sess_update.inc");
updatesession();   // ��������� ����� ������, ���� ��� ���� �������

?>

