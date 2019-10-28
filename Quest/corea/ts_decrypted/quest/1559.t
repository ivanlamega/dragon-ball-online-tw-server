CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1559;
	title = 155902;

	CNtlTSGroup
	{
		gid = 0;

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
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 155909;
				ctype = 1;
				idx = 1654105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 155908;
				gtype = 3;
				area = 155901;
				goal = 155904;
				m0fz = "964.020020";
				m0widx = 1;
				sort = 155905;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "-1991.359985";
				m0ttip = 155915;
				rwd = 100;
				taid = 1;
				title = 155902;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 2611112;
				cnt0 = 3;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 155908;
			gtype = 3;
			oklnk = 2;
			area = 155901;
			goal = 155904;
			sort = 155905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 155902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 155914;
			nextlnk = 101;
			rwdtbl = 155901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1654105;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 155907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1654105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
		}
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
	}
}

