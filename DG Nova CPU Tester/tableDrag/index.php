<?php
$con=  mysqli_connect("localhost", "root", "", "phptutorial");
$select="Select * from studentinfo Order By Position";
$result=  mysqli_query($con, $select);
$count=  mysqli_num_rows($result);
?>
<link href="bootstrapcss.css" rel="stylesheet">
<table class="table table-bordered table-striped" id="tablelist">
    <thead>
        <tr>
            <th>ID</th><th>Name</th><th>Roll</th><th>Position</th>
        </tr>
    </thead>
    <tbody>
        <?php 
        if($count<1){}else
        {
            foreach ($result as $row) {
                ?>
                <tr id="<?php echo $row["Id"]; ?>">
                    <td><?php echo $row["Id"]; ?></td>
                    <td><?php echo $row["Name"]; ?></td>
                    <td><?php echo $row["Roll"]; ?></td>
                    <td><?php echo $row["Position"]; ?></td>
                    <input type="hidden" value="<?php echo $row["Id"]; ?>" id="item" name="item">
                </tr>
                <?php 
            }
        }
        ?>
    </tbody>
</table>
<script src="jquery.min.js"></script>
<script src="jquery-ui.min_1.js"></script>
<script>
  var $sortable = $( "#tablelist > tbody" );
  $sortable.sortable({
      stop: function ( event, ui ) {
          var parameters = $sortable.sortable( "toArray" );
          $.post("studentPosition.php",{value:parameters},function(result){
              alert(result);
          });
      }
  });
</script>