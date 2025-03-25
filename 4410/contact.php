<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Contact List</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            padding: 20px;
            background: #f8f8f8;
        }
        h1 {
            color: #333;
        }
        table {
            border-collapse: collapse;
            width: 80%;
            background-color: #fff;
        }
        th, td {
            border: 1px solid #ccc;
            padding: 10px;
            text-align: left;
        }
        th {
            background-color: #eee;
        }
    </style>
</head>
<body>

<h1>📇 Contact List</h1>

<?php
// Our associative array of contacts
$contacts = [
    "alice" => [
        "name" => "Alice Smith",
        "email" => "alice@example.com",
        "city" => "Nashville"
    ],
    "bob" => [
        "name" => "Bob Johnson",
        "email" => "bob@example.com",
        "city" => "Memphis"
    ],
    "carol" => [
        "name" => "Carol White",
        "email" => "carol@example.com",
        "city" => "Knoxville"
    ]
];
?>

<table>
    <tr>
        <th>Name</th>
        <th>Email</th>
        <th>City</th>
    </tr>

    <?php foreach ($contacts as $id => $person): ?>
        <tr>
            <td><?php echo $person["name"]; ?></td>
            <td><?php echo $person["email"]; ?></td>
            <td><?php echo $person["city"]; ?></td>
        </tr>
    <?php endforeach; ?>
</table>

</body>
</html>
