CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1373;
	title = 137302;

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
				conv = 137309;
				ctype = 1;
				idx = 7131122;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 137308;
				gtype = 0;
				area = 137301;
				goal = 137304;
				grade = 132203;
				rwd = 100;
				sort = 137305;
				stype = 2;
				taid = 1;
				title = 137302;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 137314;
			nextlnk = 254;
			rwdtbl = 137301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5063103;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 137308;
			gtype = 0;
			oklnk = 2;
			area = 137301;
			goal = 137304;
			sort = 137305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 137302;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 137307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7131122;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "1356;";
			}
		}
	}
}

