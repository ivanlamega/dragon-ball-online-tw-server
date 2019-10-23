CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1323;
	title = 132302;

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
				conv = 132309;
				ctype = 1;
				idx = 1591103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 132308;
				gtype = 1;
				area = 132301;
				goal = 132304;
				grade = 132203;
				rwd = 100;
				sort = 132305;
				stype = 2;
				taid = 1;
				title = 132302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 132307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1591103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "1318;";
			}
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
			cont = 132308;
			gtype = 1;
			oklnk = 2;
			area = 132301;
			goal = 132304;
			sort = 132305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 132302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 132314;
			nextlnk = 254;
			rwdtbl = 132301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5313101;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

