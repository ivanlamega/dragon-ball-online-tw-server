CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1333;
	title = 133302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 133309;
				ctype = 1;
				idx = 2805101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 133308;
				gtype = 1;
				area = 133301;
				goal = 133304;
				grade = 132203;
				rwd = 100;
				sort = 133305;
				stype = 2;
				taid = 1;
				title = 133302;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 133314;
			nextlnk = 254;
			rwdtbl = 133301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 133307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2805101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "1332;";
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
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 133308;
			gtype = 1;
			oklnk = 2;
			area = 133301;
			goal = 133304;
			sort = 133305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 133302;
		}
	}
}

