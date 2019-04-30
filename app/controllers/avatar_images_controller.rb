class AvatarImagesController < ApplicationController
  before_action :authenticate_user!

  def update
    if current_user.update(avatar: params[:avatar])
      render json: { url: current_user.avatar.url }, status: 200
    else
      render json: { errors: ['ALgo errado aconteceu. Tente novamente.'] }, status: 422
    end
  end
end

