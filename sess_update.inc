<?
// ���������� ������������ ������ ��� ������ �� ����� �������� �����
function updatesession()
{ // ���������� ������������ ������
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
   $LogNum = $UserLogNumCookie; // ����� ������ � �������
   $StartT = $StartTimeCookie;  // ����� ������ ������
// echo "������ ������ ".$StartT;
// echo "LogNum=".$LogNum;

$EndT=time();
$T = date( "Y-m-d  H:i:s",$EndT ); // ����� ����� ������

$difft=$EndT-$StartT;  // ������������ ������ �� ������ ������, ��� ��������� ������

//echo "UserIdCookie=".$UserIdCookie;
//echo "<br> � ������� ������ ������ difft=".$difft;
$res  = db_query( "select connect_time from $tablog where num=$LogNum" );
list($prev_connect_time) = db_fetch_row( $res );  
//echo "<br> ���������� ���������� ����� ���������� prev_connect_time=".$prev_connect_time;
// $prev_connect_time ���������� ���������� ����� ����������
// ��������� � ������� ����� ������ �� ������ � ������������ ������
$res  = db_query("update $tablog set output_time='$T',connect_time='$difft' where num=$LogNum");
// �������, ������� ������� ������ � ���������� �������� ������������ ������
$difft = $difft - $prev_connect_time;
//echo "<br> � ������� ������ ���������� difft=".$difft;
// �� ��� �������� ����������� ��������� ����� ���������� � ������� �������������
$res  = db_query( "select sum_time from $tabusers where id=$id" );
list($sum_time) = db_fetch_row( $res );
$sum_time=$sum_time+$difft;
$res  = db_query("update $tabusers set sum_time='$sum_time' where id=$id");
 }
// else
// { echo "��� ����������� - ��� ����������";
// } 

}
?>