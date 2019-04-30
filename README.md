# BD-IGLike Backend

Servidor API para o front da aplicação construído em Rails

## Requisitos
Rails + RVM (Ruby 2.3.1) [Como Instalar o RVM](https://www.digitalocean.com/community/tutorials/how-to-install-ruby-on-rails-with-rvm-on-ubuntu-16-04)
PostgreSQL
Redis

## Instalação

Clone esse repositório:
```
git clone
```

Rode os servidores PostgreSQL e Redis.

Deopis execute a criação do bundle:

```
bundle install
rails db:setup
rails server -p 5000
```

As endpoints da API do frontend estão configuradas na porta 5000.