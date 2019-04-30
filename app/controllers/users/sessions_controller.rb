class Users::SessionsController < ApplicationController
  def create
    if user = User.authenticate(email_or_username, params[:password])
      render json: user, serializer: CurrentUserSerializer, status: 200
    else
      render json: { errors: ['Email e senhas inválidos'] }, status: 422
    end
  end

  private

    def email_or_username
      params[:email] || params[:username]
    end
end
