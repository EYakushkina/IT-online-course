<?
function noregistration()
{ // ����������� ��� �� ��������, ������ ����� � ������
global $monthes;
global $sr;
global $pb;
global $searchfield;
require( "forum_before.inc" );
//  echo "����������� ��� �� ��������";
print "
<tr><td>
<p class=menu><a class=m href=\"useradd.php\">�����������</a></p>
</td></tr>
<tr>
<td bgcolor=#D5DCE2><img src=\"images/spacer.gif\" height=2></td>
</tr>
<tr><td>
<p class=menu>�����������</p>
</td></tr>
<tr>
<td bgcolor=#D5DCE2>
<table cellpadding=2 cellspacing=2 border=0>
<tr>
<form name=enter action=forum.php method=post >
<td align=right><p class=logpass>���:</td>
<td><input style=\"font-size:9pt\" type=text name=inputlogin size=10></td>
</tr><tr>
<td><p class=logpass>������:</td>
<td><input style=\"font-size:9pt\" type=password name=inputpass size=10></td>
</tr><tr>
<td> &nbsp;</td>
<td align=center><input style=\"font-size:9pt\" type=submit value=\"����\" onClick=\"return CheckEnter()\"></td></form>
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

