CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1612;
	title = 161202;

	CNtlTSGroup
	{
		gid = 0;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 161207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3242201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 161214;
			nextlnk = 101;
			rwdtbl = 161201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSCheckSToCEvt
			{
				itype = 3;
			}
			CDboTSClickNPC
			{
				npcidx = 3242201;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 161209;
				ctype = 1;
				idx = 3242201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 161208;
				m1fx = "-1259.000000";
				m2fz = "-561.000000";
				m1fy = "0.000000";
				sort = 161205;
				m2widx = 1;
				grade = 132203;
				m0fx = "-1266.000000";
				m0ttip = 161215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 161202;
				gtype = 2;
				area = 161201;
				goal = 161204;
				m0fz = "2027.000000";
				m0widx = 1;
				m1ttip = 161215;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "1287.000000";
				m2fx = "-1205.000000";
				m2ttip = 161215;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 960;
				cnt0 = 15;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
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
				eitype = 3;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 161208;
			gtype = 2;
			oklnk = 2;
			area = 161201;
			goal = 161204;
			sort = 161205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 161202;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 161207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 960;
				taid = 1;
				type = 1;
			}
		}
	}
}

