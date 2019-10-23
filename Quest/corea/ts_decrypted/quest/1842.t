CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1842;
	title = 184202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 184209;
				ctype = 1;
				idx = 3142206;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 184208;
				m1fx = "1933.000000";
				area = 184201;
				goal = 184204;
				m0fz = "163.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 184216;
				sort = 184205;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "186.000000";
				grade = 132203;
				m0fx = "1980.000000";
				m0ttip = 184215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 184202;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 15;
				eitype = 0;
				idx0 = 6011101;
				cnt0 = 25;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 6012101;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 184214;
			nextlnk = 101;
			rwdtbl = 184201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3142206;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 184208;
			gtype = 2;
			oklnk = 2;
			area = 184201;
			goal = 184204;
			sort = 184205;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 184202;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 184207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3142206;
			}
			CDboTSCheckLvl
			{
				maxlvl = 45;
				minlvl = 37;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "252;0;1;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
	}
}

