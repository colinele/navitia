"""empty message

Revision ID: 3e6c7a8fbdb2
Revises: d8ce67cdcaf
Create Date: 2014-07-07 15:39:18.922191

"""

# revision identifiers, used by Alembic.
revision = '3e6c7a8fbdb2'
down_revision = 'd8ce67cdcaf'

from alembic import op
import sqlalchemy as sa


def upgrade():
    ### commands auto generated by Alembic - please adjust! ###
    op.add_column('stop_area', sa.Column('timezone', sa.String(), nullable=True))
    ### end Alembic commands ###


def downgrade():
    ### commands auto generated by Alembic - please adjust! ###
    op.drop_column('stop_area', 'timezone')
    ### end Alembic commands ###
