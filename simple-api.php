<?php

header('Content-Type: application/json');

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    http_response_code(405);
    echo json_encode(['status' => 'error', 'message' => 'Método de requisição não permitido.']);
    exit;
}

$json_data = file_get_contents('php://input');
$new_data = json_decode($json_data, true);

if (empty($new_data)) {
    http_response_code(400);
    echo json_encode(['status' => 'error', 'message' => 'Dados JSON inválidos ou ausentes.']);
    exit;
}

if (!is_array($new_data)) {
    $new_data = [$new_data];
}

$log_file = 'data.json';

if (file_exists($log_file)) {
    $existing_content = file_get_contents($log_file);
    $existing_records = json_decode($existing_content, true);
    if ($existing_records === null) {
        $existing_records = [];
    }
} else {
    $existing_records = [];
}

$all_records = array_merge($existing_records, $new_data);

$final_json = json_encode($all_records, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES);

if (file_put_contents($log_file, $final_json) === false) {
    http_response_code(500);
    echo json_encode(['status' => 'error', 'message' => 'Não foi possível escrever no arquivo de log.']);
    exit;
}

http_response_code(200);
echo json_encode(['status' => 'success', 'message' => count($new_data) . ' registros salvos com sucesso.']);
