# BD-IGLike Frontend

Réplica do Instagram na notação (single-page-application).

Utiliza:

* React
* Redux
* React-Router
* Redux Form
* Redux Thunk
* Material UI

## Configuração

### Servidor API (Backend)

É preciso rodar um servidor Rails localmente, que está localizado no outro repositório:[Backend](https://github.com/oitgg/bd-iglike-back)

Após clonar o repositório, rode os servidores PostgreSQL, Redis e Rails.
O servidor Rails deve escutar na porta 5000.
```
bundle install
rails db:setup
rails s -p 5000
```

### Servidor frontend

Clone esse repositório, e execute:
```
npm install
npm run start
```

Abra a URL `127.0.0.1:3000` no seu browser.
