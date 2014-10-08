"""shape in line and route

Revision ID: 40d9139ba0ed
Revises: 5812ecbcd76d
Create Date: 2014-10-03 17:00:06.118173

"""

# revision identifiers, used by Alembic.
revision = '40d9139ba0ed'
down_revision = '5812ecbcd76d'

from alembic import op
import sqlalchemy as sa
import geoalchemy2 as ga


def upgrade():
    op.add_column('line', schema='navitia', sa.Column('shape', ga.Geography(geometry_type='MULTILINESTRING', srid=4326, spatial_index=False), nullable=True))
    op.add_column('route', schema='navitia', sa.Column('shape', ga.Geography(geometry_type='MULTILINESTRING', srid=4326, spatial_index=False), nullable=True))


def downgrade():
    op.drop_column('route', schema='navitia', 'shape')
    op.drop_column('line', schema='navitia', 'shape')